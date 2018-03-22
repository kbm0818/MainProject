#include "../stdafx.h"
#include "ConverterScene.h"
#include "Converter.h"
#include "ConverterMaterial.h"
#include "ConverterBuffer.h"
#include "ConverterUtility.h"
#include "ConverterAnimation.h"
#include "ConverterAnimationController.h"
#include "ConverterAnimationKeyFrames.h"
#include "ConverterSkeleton.h"
#include "ConverterSkeletonBone.h"
#include "ConverterBoneWeights.h"

#include "../Utilities/String.h"

wstring ConverterScene::TexturePath = L"";

ConverterScene::ConverterScene()
	: manager(NULL), scene(NULL), converter(NULL), importer(NULL)
	, skeleton(NULL)
{
	// TexturePath의 상대경로 저장
	WCHAR folder[255];
	GetCurrentDirectory(255, folder);

	TexturePath = folder;
	TexturePath += L"\\Contents\\Converters\\Textures\\";
	animationController = new ConverterAnimationController();
}

ConverterScene::~ConverterScene()
{
	for each(ConverterMaterial* temp in materials)
		SAFE_DELETE(temp);

	for each(Converter* temp in Converters)
		SAFE_DELETE(temp);

	if (scene != NULL)scene->Destroy();
	if (manager != NULL)manager->Destroy();
}

/****************************************************************************************************
@brief
Fbx SDK 의 메모리 관리를 위한 Manager 생성 
Fbx File을 Impoter를 통하여 import시킨 후 initialize
File의 Scene정보(Material, Skeleton, Mesh, Animation) 로드
****************************************************************************************************/
void ConverterScene::LoadFbx(wstring filePath)
{
	this->filePath = filePath;

	manager = FbxManager::Create();
	assert(manager != NULL);

	scene = FbxScene::Create(manager, "");
	assert(scene != NULL);

	string tempFile = String::WStringToString(filePath);

	//SDK의 버전을 얻어온다.
	int sdkMajor, sdkMinor, sdkRevision;
	FbxManager::GetFileFormatVersion(sdkMajor, sdkMinor, sdkRevision);
	
	//임포터 생성
	importer = FbxImporter::Create(manager, "");
	bool status = importer->Initialize(tempFile.c_str(), -1, NULL);
	assert(status == true);
	
	status = importer->Import(scene);
	assert(status == true);

	converter = new FbxGeometryConverter(manager);
	{
		ProcessScene();
	}
	SAFE_DELETE(converter);

	importer->Destroy();
}

void ConverterScene::SaveBinary(wstring filePath, wstring fileName)
{
	wstring totalFileName = filePath + fileName;

	ExportMaterials(totalFileName + L"_material.bin");
	ExportSkeleton(totalFileName + L"_skeleton.bin");
	ExportConverters(totalFileName + L"_Converters.bin");
	ExportAnimations(totalFileName + L"_animations.bin");
}

void ConverterScene::LoadBinary(wstring filePath, wstring fileName)
{
	wstring totalFileName = filePath + fileName;

	ImportMaterials(totalFileName + L"_material.bin");
	ImportSkeleton(totalFileName + L"_skeleton.bin");
	ImportConverters(totalFileName + L"_Converters.bin");
	ImportAnimations(totalFileName + L"_animations.bin");
}

ConverterAnimation * ConverterScene::GetAnimation(wstring animName)
{
	map<wstring, ConverterAnimation*>::iterator iter;
	iter = animations.find(animName);
	if (iter != animations.end())
		return iter->second;

	return NULL;
}

/****************************************************************************************************
@brief
Material, Skelton, Mesh, Animation 정보를 Top->Down 방식의 재귀적 순회로 읽어들임
****************************************************************************************************/
void ConverterScene::ProcessScene()
{
	ProcessMaterial();
	ProcessNode(scene->GetRootNode(), FbxNodeAttribute::eSkeleton);
	ProcessNode(scene->GetRootNode(), FbxNodeAttribute::eMesh);
	ProcessAnimations();
}

/****************************************************************************************************
@brief
Scene안의 모든 Material 정보를 읽어, 각각의 Material 정보를 ConverterMaterial Class에 저장
****************************************************************************************************/
void ConverterScene::ProcessMaterial()
{
	for (int i = 0; i < scene->GetMaterialCount(); i++)
	{
		FbxSurfaceMaterial* temp = scene->GetMaterial(i);
		
		bool isExist = false;
		for (size_t i = 0; i < fbxMaterials.size(); i++)
		{
			if (*temp == *fbxMaterials[i]) isExist = true;
		}

		if (isExist == false)
		{
			ConverterMaterial* material = new ConverterMaterial(i, temp);

			materials.push_back(material);
			fbxMaterials.push_back(temp);
		}
	}
}

/****************************************************************************************************
@brief
Node의 정보를 로드
각 Node의 속성(Skeelton, Mesh 외의 나머지 속성은 불필요하므로 로드하지 않음)별로 순회
함수 내에서 재귀적으로 모든 자식 Node에 대하여 수행

@param FbxNode* node 최초 실행시 Root Node로 한번 실행, 이후 재귀적으로 자식 노드를 받음
@param FbxNodeAttribute::EType attribute 노드의 속성(Skeleton, Mesh...)
****************************************************************************************************/
void ConverterScene::ProcessNode(FbxNode * node, FbxNodeAttribute::EType attribute)
{	
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();
	if (nodeAttribute != NULL)
	{
		if (nodeAttribute->GetAttributeType() == attribute)
		{
			switch (nodeAttribute->GetAttributeType())
			{
				case FbxNodeAttribute::eSkeleton:
				{
					ProcessSkeleton(node);
				}	
				break;

				case FbxNodeAttribute::eMesh:
				{
					ProcessMesh(node);
				}	
				break;

				case FbxNodeAttribute::eMarker:
				case FbxNodeAttribute::eNurbs:
				case FbxNodeAttribute::ePatch:
				case FbxNodeAttribute::eCamera:
				case FbxNodeAttribute::eLight:
				case FbxNodeAttribute::eNull:
					break;
			}//switch
		}//if
	}//if(nodeAttribute)

	for (int i = 0; i < node->GetChildCount(); i++)
		ProcessNode(node->GetChild(i), attribute);
}

/****************************************************************************************************
@brief
Bone의 계층구조를 가지는 Skeleton 정보를 로드하여 ConverterSkeleton Class에 저장
****************************************************************************************************/
void ConverterScene::ProcessSkeleton(FbxNode * node)
{
	FbxSkeleton* fbxSkeleton = node->GetSkeleton();
	if (fbxSkeleton == NULL)
		return;

	if (skeleton == NULL)
		skeleton = new ConverterSkeleton();


	int parentBoneIndex = -1;
	FbxNode* parentNode = node->GetParent();
	if (parentNode != NULL)
	{
		wstring boneName = String::StringToWString(parentNode->GetName());
		parentBoneIndex = skeleton->FindBoneIndex(boneName);
	}

	// ConverterSkeleton Class에 각 Bone의 정보를 ConverterSkeletonBone Class로 저장
	wstring boneName = String::StringToWString(node->GetName());
	ConverterSkeletonBone* skeletonBone = new ConverterSkeletonBone(boneName, parentBoneIndex);
	skeleton->AddSkeletonBone(skeletonBone);
}

/****************************************************************************************************
@brief
Mesh 정보를 로드하여 Converter Class에 저장
각 Mesh 정보(Global Transform, Geomatric Offset)를 Converter Class에
각 Vertex의 정보(Pos, Normal, Uv, BoneWeight)는 Material 별로 나뉘어 Converter Class안의 Part Class에 저장
****************************************************************************************************/
void ConverterScene::ProcessMesh(FbxNode * node)
{
	// Mesh 정보를 읽어올 때, 기본 구성 단위를 삼각형으로 읽기
	FbxNodeAttribute* attribute = node->GetNodeAttribute();
	converter->Triangulate(attribute, true, true);

	FbxMesh* mesh = node->GetMesh();
	assert(mesh != NULL);

	int vertexCount = mesh->GetControlPointsCount();
	assert(vertexCount > 0);

	// Vertex의 수만큼 ConverterBoneWeights Class를 할당
	vector<ConverterBoneWeights> boneWeights(vertexCount, ConverterBoneWeights());
	ProcessBoneWeights(mesh, boneWeights);

	// BoneWeights의 정보를 담고있는 ConverterBuffer는 Converter -> Part까지 전달
	Converter* Converter = new Converter(this, String::StringToWString(node->GetName()));

	// Control Point는 Vertex의 물리적인 정보, (i.e. 육면체의 경우 4개)
	FbxVector4* controlPoints = mesh->GetControlPoints();

	// Mesh의 Polygon(삼각형)수만큼 반복
	for (int i = 0; i < mesh->GetPolygonCount(); i++)
	{
		ConverterMaterial* material = NULL;

		// Polygon의 세 점
		for (int vi = 0; vi < 3; vi++)
		{
			// i번째 Polygon의 vi(0~2)번째 Vertex의 Vertex Index를 구함
			int vertexIndex = mesh->GetPolygonVertex(i, vi);
			if (vertexIndex < 0 || vertexIndex >= vertexCount)
				continue;

			if (material == NULL)
				material = LinkMaterialWithPolygon(mesh, 0, i, 0, vertexIndex);

			FbxVector4 fbxPos = controlPoints[vertexIndex];
			FbxVector4 fbxNormal;
			mesh->GetPolygonVertexNormal(i, vi, fbxNormal);
			fbxNormal.Normalize();

			D3DXVECTOR3 vecPos = ConverterUtility::ToVector3(fbxPos);
			D3DXVECTOR3 vecNormal = ConverterUtility::ToVector3(fbxNormal);

			D3DXVECTOR2 vecUv = GetUV(mesh, 0, i, vi, vertexIndex);

			// Converter 에 Vertex정보를 추가(Converter에서 Material별로 나누어 각 Part에 추가)
			Converter->AddVertex(material, vecPos, vecNormal, vecUv, boneWeights[vertexIndex]);
		}//for(vi)
	}//for(i)

	 // Mesh의 Global TransForm(루트->모델) 을 AbsoluteTransform에 저장
	D3DXMATRIX temp = GetAbsoluteTransformFromCurrentTake(node, FbxTime(0));
	Converter->SetAnimationTransform(temp);
	// Mesh의 GeobetrixOffset을 추가(대부분의 경우 Identity Matrix)
	Converter->SetGeometricOffset(GetGeometricOffset(node));

	Converter->CreateData();
	Converter->CreateBuffer();

	Converters.push_back(Converter);
}

/****************************************************************************************************
@brief
Animation 정보를 로드하여 ConverterAnimationController Class 에 저장
****************************************************************************************************/
void ConverterScene::ProcessAnimations()
{
	FbxNode* rootNode = scene->GetRootNode();
	if (rootNode == NULL) return;

	// Fbx File 내에 설정된 Frame Rate(초당 실행할 Frame수)를 로드
	float frameRate = (float)FbxTime::GetFrameRate(scene->GetGlobalSettings().GetTimeMode());

	// animationArray에 Animation 이름을 로드하여 저장
	FbxArray<FbxString *> animationArray;
	FbxDocument* document = dynamic_cast<FbxDocument *>(scene);
	if (document != NULL)
		document->FillAnimStackNameArray(animationArray);

	UINT animationCount = importer->GetAnimStackCount();
	// importer로 부터 FBX에 저장된 모든 Animation 정보를 로드
	for (int i = 0; i < animationCount; i++)
	{
		FbxTakeInfo* animationInfo = importer->GetTakeInfo(i);
		wstring animationName = String::StringToWString(animationInfo->mImportName.Buffer());

		// FbxTimeSpan: 구간 시간을 저장하는 Class
		FbxTimeSpan span = animationInfo->mLocalTimeSpan;
	
		// 초 단위로 시작, 끝 시간을 로드하여 할당
		double startTime = span.GetStart().GetSecondDouble();
		double endTime = span.GetStop().GetSecondDouble();

		if (startTime < endTime)
		{
			// KeyFrames의 수 = Animation 실행 시간(초) * 초당 Frmae 수
			int keyFrameCount = (int)((endTime - startTime) * (double)frameRate);

			// AnimationController에 ConverterAnimation Class로 정보를 저장
			ConverterAnimation* animation = new ConverterAnimation(animationName, keyFrameCount, frameRate);
			AddAnimation(animation);

			animationController->AddAnimation(animation);
			
			// 기본 Animation 정보를 이용하여, Skeleton, Mesh의 Animation 정보 계산
			ProcessAnimation(rootNode, animationName, frameRate, (float)startTime, (float)endTime);
		}
	}
	animationArray.Clear();

	// 마지막에 추가된 애니메이션을 현재 애니메이션으로 설정 후 플레이
	animationController->SetCurrentAnimation(animationCount-1);
	animationController->Play();

	//TODO: defualt 스택 세팅
}


/****************************************************************************************************
@brief
해당 Animation의 각 Bone과 Mesh의 모든 KeyFrame 정보를 계산하여 animationKeyFrames에 할당하여
각 Bone과 Mesh에 해당하는 ConverterSkeletonBone, Converter Class에 저장
****************************************************************************************************/
void ConverterScene::ProcessAnimation(FbxNode * node, wstring animationName, float frameRate, float start, float stop)
{
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();
	if (nodeAttribute != NULL)
	{
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			if (skeleton != NULL)
			{
				wstring boneName = String::StringToWString(node->GetName());
				ConverterSkeletonBone* bone = skeleton->FindBone(boneName);

				if (bone != NULL)
				{
					ConverterAnimationKeyFrames* animationKeyFrames = new ConverterAnimationKeyFrames(animationName);

					double time = 0;
					// Animation의 실행 시간 안에서, Frame Time 마다 KeyFrame을 추가
					// 각 KeyFrame Class에 해당 Bone의 해당 시간에서의 Local Transform Matrix(부모 본-> 자신 본)를 로드하여 저장

					while (time <= (double)stop)
					{
						FbxTime animationTime;
						animationTime.SetSecondDouble(time);
						
						//// Bone 자신의 Global Transform(자신 본 -> 루트)을 저장
						//D3DXMATRIX matAbsoluteTransform = GetAbsoluteTransformFromCurrentTake(node, animationTime);
						//// 부모 Bone 의 Global Transform(부모 본 -> 루트)을 저장
						//D3DXMATRIX matParentAbsoluteTransform = GetAbsoluteTransformFromCurrentTake(node->GetParent(), animationTime);
						//
						//// 부모 Bone 의 Global Transform(부모 본 -> 루트)의 Inverse Transform(루트 -> 부모 본)를 저장
						//D3DXMATRIX matInvParentAbsoluteTransform;
						//D3DXMatrixInverse(&matInvParentAbsoluteTransform, NULL, &matParentAbsoluteTransform);
						//
						//// matTransform = (자신 본 -> 루트) * (루트 -> 부모 본) == (자신 본 -> 부모 본)
						//// 부모 Bone 좌표계에서의 Bone의 Transform Matrix
						//D3DXMATRIX localTransform = matAbsoluteTransform * matInvParentAbsoluteTransform;
						

						// Local Transform = 부모 Bone의 Global Trasforn 의 Inverse Transform * 자신 Bone의 Global Transform
						D3DXMATRIX localTransform = GetLocalTransformFromCurrentTake(node, animationTime);
						animationKeyFrames->AddKeyFrame(localTransform);

						time += 1.0f / frameRate;
					}

					bone->AddAnimationKeyFrames(animationKeyFrames);
				}//if(bone)
			}//if(skeleton)
		}
		else if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			Converter* Converter = NULL;
			for each(Converter* tempConverter in Converters)
			{
				wstring ConverterName = String::StringToWString(node->GetName());
				if (ConverterName == tempConverter->GetName())
				{
					Converter = tempConverter;

					break;
				}
			}

			if (Converter != NULL)
			{
				ConverterAnimationKeyFrames* animationKeyFrames = new ConverterAnimationKeyFrames(animationName);

				double time = 0;
				while (time <= (double)stop)
				{
					FbxTime animationTime;
					animationTime.SetSecondDouble(time);

					// Mesh는 모두 GlobalTransform Matrix(루트->매쉬) 정보로 저장
					D3DXMATRIX matAbsoluteTransform = GetAbsoluteTransformFromCurrentTake(node, animationTime);
					animationKeyFrames->AddKeyFrame(matAbsoluteTransform);

					time += 1.0f / frameRate;
				}

				Converter->AddAnimationKeyFrames(animationKeyFrames);
			}
		}//if(nodeAttribute->GetAttributeType())
	}//if(nodeAttribute)

	// 자식 node(Bone)을 재귀적으로 순회
	for (int i = 0; i < node->GetChildCount(); ++i)
		ProcessAnimation(node->GetChild(i), animationName, frameRate, start, stop);
}

/****************************************************************************************************
@brief
Mesh의 Skin 정보를 로드하여, 해당 Mesh가 각 Bone에 대하여 얼만큼의 영향을 받는지(Weight)를 로드
****************************************************************************************************/
void ConverterScene::ProcessBoneWeights(FbxMesh * mesh, vector<ConverterBoneWeights>& meshBoneWeights)
{
	if (skeleton == NULL)
		return;

	// Deformer는 주로 Scene에서 하나만 존재
	for (int i = 0; i < mesh->GetDeformerCount(); ++i)
	{
		FbxDeformer* deformer = mesh->GetDeformer(i);

		if (deformer == NULL)
			continue;

		// Deformer의 타입이 Skin일 경우, 즉 Skinned Mesh일 경우
		if (deformer->GetDeformerType() == FbxDeformer::eSkin)
		{
			
			FbxSkin* skin = (FbxSkin *)deformer;

			if (skin == NULL)
				continue;

			ProcessBoneWeights(skin, meshBoneWeights);
		}
	}
}

/****************************************************************************************************
 @brief
 Skin 정보를 로드하여, Mesh의 해당 Vertex가 각 Bone에 대하여 얼만큼의 영향을 받는지(Weight)를
 ConverterBoneWeights Class의 Vector에 저장(크기: VertexCount, Index: VertexIndex)
****************************************************************************************************/
void ConverterScene::ProcessBoneWeights(FbxSkin * skin, vector<ConverterBoneWeights>& meshBoneWeights)
{
	FbxCluster::ELinkMode linkMode = FbxCluster::eNormalize;

	int clusterCount = skin->GetClusterCount();
	vector<ConverterBoneWeights> skinBoneWeights(meshBoneWeights.size(), ConverterBoneWeights());
	for (int i = 0; i < clusterCount; i++)
	{
		FbxCluster* cluster = skin->GetCluster(i);
		if (cluster == NULL)
			continue;

		linkMode = cluster->GetLinkMode();
		FbxNode* pLinkNode = cluster->GetLink();

		if (pLinkNode == NULL)
			continue;

		wstring lineNodeName = String::StringToWString(pLinkNode->GetName());
		int nBoneIndex = skeleton->FindBoneIndex(lineNodeName);
		if (nBoneIndex < 0)
			continue;

		ConverterSkeletonBone* skeletonBone = skeleton->GetSkeletonBone(nBoneIndex);

		FbxAMatrix matClusterTransformMatrix;
		FbxAMatrix matClusterLinkTransformMatrix;
		cluster->GetTransformMatrix(matClusterTransformMatrix); // 매쉬의 Transform Matrix
		cluster->GetTransformLinkMatrix(matClusterLinkTransformMatrix); // 본의 Transform Matrix

																		//TODO: 체크
		skeletonBone->SetBindPoseTransform(ConverterUtility::ToMatrix(matClusterLinkTransformMatrix)); // 본->루트
		skeletonBone->SetBoneReferenceTransform(ConverterUtility::ToMatrix(matClusterTransformMatrix)); // 매쉬->루트

		int* indices = cluster->GetControlPointIndices(); //해당 Bone에 영향을 받는 모든 Vertex Index값의 배열
		double* weights = cluster->GetControlPointWeights(); // 각 Vertex Index가 갖는 Weight값의 배열

															 // indices[j]의 Index를 갖는 Vertex에 영향을 주는 Bone의 Idx와, 그 수치인 Weights를
															 // ConverterBoneWeights Class로 형식으로 추가
		for (int j = 0; j < cluster->GetControlPointIndicesCount(); ++j)
			skinBoneWeights[indices[j]].AddBoneWeight(nBoneIndex, (float)weights[j]);
	}

	// Weight의 모드
	switch (linkMode)
	{
		case FbxCluster::eNormalize: // 모든 Weight의 합이 1 로 정규화
			{
				for (int i = 0; i < (int)skinBoneWeights.size(); ++i)
					skinBoneWeights[i].Normalize();
			}
			break;

		case FbxCluster::eAdditive: // 그대로 합산
			break;

		case FbxCluster::eTotalOne: // 모든 Weight의 합이 1 이어야 함(정규화 되지 않음)
			break;
	}

	for (size_t i = 0; i < meshBoneWeights.size(); i++)
		meshBoneWeights[i].AddBoneWeights(skinBoneWeights[i]);
}

/****************************************************************************************************
 @biref
 해당 Vertex Index의 Material 정보를 ConverterMaterial Class 형식으로 반환
****************************************************************************************************/
ConverterMaterial * ConverterScene::LinkMaterialWithPolygon(FbxMesh * mesh, int layerIndex, int polygonIndex, int polygonVertexIndex, int vertexIndex)
{
	if (layerIndex < 0 || layerIndex > mesh->GetLayerCount())
		return NULL;

	
	FbxNode* node = mesh->GetNode();
	if (node == NULL) return NULL;

	FbxLayerElementMaterial* fbxMaterial = mesh->GetLayer(layerIndex)->GetMaterials();
	if (fbxMaterial == NULL) return NULL;

	int mappingIndex = GetMappingIndex
	(
		fbxMaterial->GetMappingMode()
		, polygonIndex
		, 0
		, vertexIndex
	);
	if (mappingIndex < 0) return NULL;

	// Material이 Vertex Index에 적용된 모드를 로드한 후,
	// 이에 맞도록 mappingIndex를 계산 후, GetMaterial로 해당 Vertex의 Material 을 반환
	FbxLayerElement::EReferenceMode refMode = fbxMaterial->GetReferenceMode();
	if (refMode == FbxLayerElement::eDirect)
	{
		if (mappingIndex < node->GetMaterialCount())
			return GetMaterial(node->GetMaterial(mappingIndex));
	}
	else if (refMode == FbxLayerElement::eIndexToDirect)
	{
		FbxLayerElementArrayTemplate<int>& indexArr = fbxMaterial->GetIndexArray();

		if (mappingIndex < indexArr.GetCount())
		{
			int tempIndex = indexArr.GetAt(mappingIndex);

			if (tempIndex < node->GetMaterialCount())
				return GetMaterial(node->GetMaterial(tempIndex));
		}//if(mappingIndex)
	}//if(refMode)

	return NULL;
}

/****************************************************************************************************
@biref
MappingMode에 따른 Index를 계산하여 반환
****************************************************************************************************/
int ConverterScene::GetMappingIndex(FbxLayerElement::EMappingMode mode, int polygonIndex, int polygonVertexIndex, int vertexIndex)
{
	switch (mode)
	{
		case FbxLayerElement::eAllSame: 
			return 0;
		case FbxLayerElement::eByControlPoint: 
			return vertexIndex;
		case FbxLayerElement::eByPolygonVertex: 
			return polygonIndex * 3 + polygonVertexIndex;
		case FbxLayerElement::eByPolygon:
			return polygonIndex;
	}
	
	return -1;
}

/****************************************************************************************************
@biref
해당 Vertex Index의 UV값을 로드하여 반환
****************************************************************************************************/
D3DXVECTOR2 ConverterScene::GetUV(FbxMesh * mesh, int layerIndex, int polygonIndex, int polygonVertexIndex, int vertexIndex)
{
	int layerCount = mesh->GetLayerCount();
	if (layerIndex >= layerCount) return D3DXVECTOR2();

	FbxLayer* layer = mesh->GetLayer(layerIndex);
	if(layer == NULL) return D3DXVECTOR2();

	// Diffuse Texture의 Uv로드
	FbxLayerElementUV* uv = layer->GetUVs(FbxLayerElement::eTextureDiffuse);
	if(uv == NULL) return D3DXVECTOR2();


	FbxLayerElement::EMappingMode mappingMode = uv->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = uv->GetReferenceMode();

	const FbxLayerElementArrayTemplate<FbxVector2>& uvArray = uv->GetDirectArray();
	const FbxLayerElementArrayTemplate<int>& uvIndexArray = uv->GetIndexArray();

	int mappingIndex = 0;
	if (mappingMode == FbxLayerElement::eByControlPoint)
	{
		mappingIndex = vertexIndex;

		if (refMode == FbxLayerElement::eDirect)
		{
			if(mappingIndex < uvArray.GetCount())
				return ConverterUtility::ToUv(uvArray.GetAt(mappingIndex));
		}
		else if (refMode == FbxLayerElement::eIndexToDirect)
		{
			if (mappingIndex < uvArray.GetCount())
			{
				int tempIndex = uvIndexArray.GetAt(mappingIndex);

				if(tempIndex < uvIndexArray.GetCount())
					return ConverterUtility::ToUv(uvArray.GetAt(tempIndex));
			}
		}//if(refMode)
	}
	else if (mappingMode == FbxLayerElement::eByPolygonVertex)
	{
		mappingIndex = mesh->GetTextureUVIndex
		(
			polygonIndex
			, polygonVertexIndex
			, FbxLayerElement::eTextureDiffuse
		);

		switch (refMode)
		{
			case FbxLayerElement::eDirect:
			case FbxLayerElement::eIndexToDirect:
				if (mappingIndex < uvArray.GetCount())
					return ConverterUtility::ToUv(uvArray.GetAt(mappingIndex));
		}//switch(refMode)
	}//if(mappingMode)

	return D3DXVECTOR2();
}

/****************************************************************************************************
 @biref
 FbxSurfaceMaterial 으로 저장된 값을 ConverterMaterial Class로 변환
****************************************************************************************************/
ConverterMaterial * ConverterScene::GetMaterial(FbxSurfaceMaterial * fbxMaterial)
{
	for (size_t i = 0; i < fbxMaterials.size(); i++)
	{
		if (fbxMaterials[i] == fbxMaterial)
			return materials[i];
	}

	return NULL;
}

/****************************************************************************************************
 @biref
 Node의 Offset Transform Matrix를 반환
****************************************************************************************************/
D3DXMATRIX ConverterScene::GetGeometricOffset(FbxNode * node)
{
	if (node == NULL)
	{
		D3DXMATRIX matrix;
		D3DXMatrixIdentity(&matrix);

		return matrix;
	}

	FbxVector4 T = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = node->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = node->GetGeometricScaling(FbxNode::eSourcePivot);

	FbxAMatrix offset = FbxAMatrix(T, R, S);

	return ConverterUtility::ToMatrix(offset);
}

/****************************************************************************************************
 @biref
 임의의 time에서 node의 Global Transform Matrix(노드->루트)를 로드하여 반환
****************************************************************************************************/
D3DXMATRIX ConverterScene::GetAbsoluteTransformFromCurrentTake(FbxNode * node, FbxTime time)
{
	if (node == NULL)
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);

		return mat;
	}
	
	FbxAMatrix matrix = node->EvaluateGlobalTransform(time);
	
	return ConverterUtility::ToMatrix(matrix);
}

/****************************************************************************************************
 @biref
 임의의 time에서 node의 Local Transform Matrix(자신->부모)를 로드하여 반환
****************************************************************************************************/
D3DXMATRIX ConverterScene::GetLocalTransformFromCurrentTake(FbxNode * node, FbxTime time)
{
	if( node == NULL )
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);

		return mat;
	}

	FbxAMatrix matrix = node->EvaluateLocalTransform(time);

	return ConverterUtility::ToMatrix(matrix);
}

void ConverterScene::AddAnimation(ConverterAnimation * animation)
{
	wstring animName = animation->GetName();
	if (animations.count(animName) > 0)
		return;
	else
		animations.insert({ animName, animation });
}


// Binary Export 관련
void ConverterScene::ExportMaterials(wstring fileName)
{
	BinaryWriter bMaterials = BinaryWriter();
	bMaterials.Open(fileName);
	{
		bMaterials.Write(materials);
	}
	bMaterials.Close();
}

void ConverterScene::ExportSkeleton(wstring fileName)
{
	BinaryWriter bSkeleton = BinaryWriter();
	bSkeleton.Open(fileName);
	{
		bSkeleton.Write(skeleton);
	}
	bSkeleton.Close();
}

void ConverterScene::ExportConverters(wstring fileName)
{
	BinaryWriter bConverters = BinaryWriter();
	bConverters.Open(fileName);
	{
		bConverters.Write(Converters);
	}
	bConverters.Close();
}

void ConverterScene::ExportAnimations(wstring fileName)
{
	BinaryWriter bAnimations = BinaryWriter();
	bAnimations.Open(fileName);
	{
		bAnimations.Write(animations);
	}
	bAnimations.Close();
}

void ConverterScene::ImportMaterials(wstring fileName)
{
	BinaryReader bMaterials = BinaryReader();
	bMaterials.Open(fileName);
	{
		UINT materialsCount = bMaterials.UInt();
		materials.clear();
		materials.reserve(materialsCount);
		for (size_t i = 0; i < materialsCount; i++)
		{
			ConverterMaterial* material = new ConverterMaterial();
			material->Import(&bMaterials);
			materials.push_back(material);
		}
	}
	bMaterials.Close();
}

void ConverterScene::ImportSkeleton(wstring fileName)
{
	BinaryReader bSkeleton = BinaryReader();
	bSkeleton.Open(fileName);
	{
		skeleton = new ConverterSkeleton();
		skeleton->Import(&bSkeleton);
	}
	bSkeleton.Close();
}

void ConverterScene::ImportConverters(wstring fileName)
{
	BinaryReader bConverters = BinaryReader();
	bConverters.Open(fileName);
	{
		UINT ConvertersCount = bConverters.UInt();
		Converters.clear();
		Converters.reserve(ConvertersCount);
		for (size_t i = 0; i < ConvertersCount; i++)
		{
			Converter* Converter = new Converter(this);
			Converter->Import(&bConverters);
			Converters.push_back(Converter);
		}
	}
	bConverters.Close();
}

void ConverterScene::ImportAnimations(wstring fileName)
{
	BinaryReader bAnimations = BinaryReader();
	bAnimations.Open(fileName);
	{
		animations.clear();
		UINT animationKeyFramesCount = bAnimations.UInt();
		
		if (animationKeyFramesCount > 0 && animationController == NULL)
			animationController = new ConverterAnimationController();

		for (size_t i = 0; i < animationKeyFramesCount; i++)
		{
			wstring name = bAnimations.WString();
			ConverterAnimation* ConverterAnimation = new ConverterAnimation();
			ConverterAnimation->Import(&bAnimations);
			animations.insert(make_pair(name, ConverterAnimation));

			animationController->AddAnimation(ConverterAnimation);
		}

		animationController->SetCurrentAnimation(animationKeyFramesCount-1);
		animationController->Play();
	}
	bAnimations.Close();
}
