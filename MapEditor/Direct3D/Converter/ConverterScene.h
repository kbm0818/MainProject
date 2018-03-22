#pragma once
#include "ConverterEnums.h"

class Converter;
class ConverterMaterial;
class ConverterBuffer;
class ConverterSkeleton;
class ConverterAnimation;
class ConverterAnimationController;
class ConverterBoneWeights;

class ConverterScene
{
public:
	ConverterScene();
	~ConverterScene();

	static wstring TexturePath;

	//wstring GetFileName() { return fileName; }
	vector<ConverterMaterial*>* GetMaterials() { return &materials; }
	vector<Converter*>* GetConverters() { return &Converters; }
	ConverterSkeleton* GetSkeleton() { return skeleton; }
	ConverterAnimation* GetAnimation(wstring animName);

	void LoadFbx(wstring filePath);
	void SaveBinary(wstring filePath, wstring fileName);
	void LoadBinary(wstring filePath, wstring fileName);

private:
	void ProcessScene();
	void ProcessMaterial();
	void ProcessNode(FbxNode* node, FbxNodeAttribute::EType attribute);
	void ProcessSkeleton(FbxNode* node);
	void ProcessMesh(FbxNode* node);
	void ProcessAnimations();
	void ProcessAnimation(FbxNode* node, wstring takeName, float frameRate, float start, float stop);

	void ProcessBoneWeights(FbxMesh* mesh, vector<ConverterBoneWeights>& meshBoneWeights);
	void ProcessBoneWeights(FbxSkin* skin, vector<ConverterBoneWeights>& meshBoneWeights);
	
	ConverterMaterial* LinkMaterialWithPolygon
	(
		FbxMesh* mesh, int layerIndex
		, int polygonIndex, int polygonVertexIndex
		, int vertexIndex
	);

	int GetMappingIndex
	(
		FbxLayerElement::EMappingMode mode
		, int polygonIndex
		, int polygonVertexIndex
		, int vertexIndex
	);

	D3DXVECTOR2 GetUV
	(
		FbxMesh* mesh, int layerIndex
		, int polygonIndex, int polygonVertexIndex
		, int vertexIndex
	);

	ConverterMaterial* GetMaterial(FbxSurfaceMaterial* fbxMaterial);
	D3DXMATRIX GetGeometricOffset(FbxNode* node);
	D3DXMATRIX GetAbsoluteTransformFromCurrentTake(FbxNode* node, FbxTime time);
	D3DXMATRIX GetLocalTransformFromCurrentTake(FbxNode* node, FbxTime time);
	void AddAnimation(ConverterAnimation* animation);

	void ExportMaterials(wstring fileName);
	void ExportSkeleton(wstring fileName);
	void ExportConverters(wstring fileName);
	void ExportAnimations(wstring fileName);

	void ImportMaterials(wstring fileName);
	void ImportSkeleton(wstring fileName);
	void ImportConverters(wstring fileName);
	void ImportAnimations(wstring fileName);

	wstring filePath;

	FbxManager* manager;
	FbxScene* scene;
	FbxGeometryConverter* converter;
	FbxImporter* importer;

	vector<ConverterMaterial*> materials;
	vector<FbxSurfaceMaterial*> fbxMaterials;
	ConverterSkeleton* skeleton;
	vector<Converter*> Converters;
	map<wstring, ConverterAnimation*> animations;

	ConverterAnimationController* animationController;
};