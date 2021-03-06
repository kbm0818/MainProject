#include "../stdafx.h"
#include "ConverterPart.h"
#include "ConverterScene.h"
#include "Converter.h"
#include "ConverterMaterial.h"
#include "ConverterBoneWeights.h"
#include "ConverterBuffer.h"

ConverterPart::ConverterPart(Converter * Converter)
	: Shader(L"./Converter/Converter.fx")
	, Converter(Converter), material(NULL)
	, vertex(NULL), index(NULL)
	, vertexBuffer(NULL), indexBuffer(NULL)
{
	CreateInputLayout(VertexTextureNormalTangentBlend::desc, VertexTextureNormalTangentBlend::count);
}

ConverterPart::ConverterPart(Converter* Converter, ConverterMaterial* material)
	: Shader(L"./Converter/Converter.fx")
	, Converter(Converter), material(material)
	, vertex(NULL), index(NULL)
	, vertexBuffer(NULL), indexBuffer(NULL)
{
	materialIndex = material->GetIndex();
	CreateInputLayout(VertexTextureNormalTangentBlend ::desc, VertexTextureNormalTangentBlend::count);
}

ConverterPart::ConverterPart(ConverterPart & otherConverterPart)
	: Shader(L"./Converter/Converter.fx")
	, vertex(NULL), index(NULL)
	, vertexBuffer(NULL), indexBuffer(NULL)
{
	Converter = (Converter != NULL) ? otherConverterPart.Converter : NULL;

	positions = otherConverterPart.positions;
	normals = otherConverterPart.normals;
	tangents = otherConverterPart.tangents;
	uvs = otherConverterPart.uvs;
	indices = otherConverterPart.indices;
	boneWeights = otherConverterPart.boneWeights;

	vertexCount = otherConverterPart.vertexCount;
	vertex = new VertexTextureNormalTangentBlend[vertexCount];
	memcpy(vertex, otherConverterPart.vertex, vertexCount * sizeof(VertexTextureNormalTangentBlend));

	indexCount = otherConverterPart.indexCount;
	index = new UINT[indexCount];
	memcpy(index, otherConverterPart.index, indexCount * sizeof(UINT));

	//ConverterBuffer = (ConverterBuffer != NULL) ? otherConverterPart.ConverterBuffer : NULL;
	material = (material != NULL) ? otherConverterPart.material : NULL;

	isSkinnedConverter = otherConverterPart.isSkinnedConverter;

	CreateInputLayout(VertexTextureNormalTangentBlend::desc, VertexTextureNormalTangentBlend::count);

	CreateBuffer();
}

ConverterPart::~ConverterPart()
{
	SAFE_DELETE_ARRAY(vertex);
	SAFE_DELETE_ARRAY(index);

	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}

void ConverterPart::Update(bool isAnimation)
{
	D3DXMATRIX world;
	if (isAnimation == true)
	{
		if (isSkinnedConverter == true)
			world = Converter->GetGeometricOffset();
		else
			world = Converter->GetGeometricOffset() * Converter->GetAnimationTransform();
	}
	else
		world = Converter->GetGeometricOffset();

	world *= Converter->GetAbsoluteTransform();
	worldBuffer->SetWorld(world);

	Shader::Update();
}

void ConverterPart::Render()
{
	ID3D11DeviceContext* dc = D3D::GetDeviceContext();

	UINT stride = sizeof(VertexTextureNormalTangentBlend);
	UINT offset = 0;

	dc->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	dc->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	ID3D11ShaderResourceView* diffuseView = material->GetDiffuseView();
	dc->PSSetShaderResources(0, 1, &diffuseView);
	
	ID3D11ShaderResourceView* normalmapView = material->GetNormalMapView();
	dc->PSSetShaderResources(1, 1, &normalmapView);

	ID3D11ShaderResourceView* specularmapView = material->GetSpecularView();
	dc->PSSetShaderResources(2, 1, &specularmapView);

	Shader::Render();
	
	dc->DrawIndexed(indexCount, 0, 0);
}

void ConverterPart::AddVertex(D3DXVECTOR3 & position, D3DXVECTOR3 & normal, D3DXVECTOR2 & uv, const ConverterBoneWeights& boneWeights)
{
	positions.push_back(position);
	normals.push_back(normal);
	tangents.push_back(D3DXVECTOR3(0, 0, 0));
	uvs.push_back(uv);
	indices.push_back((UINT)indices.size());
	
	this->boneWeights.push_back(boneWeights);
	if (boneWeights.GetBoneWeightCount() > 0)
		isSkinnedConverter = true;
}

void ConverterPart::CreateData()
{
	vertexCount = positions.size();
	indexCount = indices.size();

	vertex = new VertexTextureNormalTangentBlend[vertexCount];
	for (UINT i = 0; i < vertexCount; i++)
	{
		vertex[i].position = positions[i];
		vertex[i].normal = normals[i];
		vertex[i].uv = uvs[i];
	}

	for (UINT i = 0; i < boneWeights.size(); i++)
	{
		ConverterBlendWeights weight = boneWeights[i].GetBlendWeights();
		vertex[i].blendIndices = weight.BlendIndices;
		vertex[i].blendWeights = weight.BlendWeights;
	}

	index = new UINT[indexCount];
	for (UINT i = 0; i < indexCount; i++)
		index[i] = indices[i];

	// Tangent 계산
	CalculateTangents();
	for (UINT i = 0; i < vertexCount; i++)
		vertex[i].tangent = tangents[i];
}

void ConverterPart::CreateBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA data;

	//1. Vertex Buffer
	if (vertexBuffer != NULL)
		SAFE_RELEASE(vertexBuffer);

	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(VertexTextureNormalTangentBlend) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertex;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));


	//2. Index Buffer
	if (indexBuffer != NULL)
		SAFE_RELEASE(indexBuffer);

	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = index;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
	assert(SUCCEEDED(hr));
}

void ConverterPart::Export(BinaryWriter * bw)
{
	bw->Write(isSkinnedConverter);

	bw->Write(materialIndex);

	bw->Write(vertexCount);
	bw->Write(vertex, sizeof(VertexTextureNormalTangentBlend), vertexCount);

	bw->Write(indexCount);
	bw->Write(index, sizeof(UINT), indexCount);
}

void ConverterPart::Import(BinaryReader * br)
{
	isSkinnedConverter = br->Bool();

	materialIndex = br->UInt();
	ConverterScene* scene = Converter->GetConverterScene();
	vector<ConverterMaterial*>* materials = scene->GetMaterials();
	UINT size = materials->size();
	material = materials->at(materialIndex);

	vertexCount = br->UInt();
	SAFE_DELETE_ARRAY(vertex);
	vertex = new VertexTextureNormalTangentBlend[vertexCount];
	br->Read(vertex, sizeof(VertexTextureNormalTangentBlend), vertexCount);

	indexCount = br->UInt();
	SAFE_DELETE_ARRAY(index);
	index = new UINT[indexCount];
	br->Read(index, sizeof(UINT), indexCount);

	CreateBuffer();
}

void ConverterPart::CalculateTangents()
{
	D3DXVECTOR3* tempTangents = new D3DXVECTOR3[vertexCount];
	ZeroMemory(tempTangents, vertexCount * sizeof(D3DXVECTOR3));

	D3DXVECTOR3* tempBinormals= new D3DXVECTOR3[vertexCount];
	ZeroMemory(tempBinormals, vertexCount * sizeof(D3DXVECTOR3));

	UINT triangleCount = indexCount / 3;

	for (UINT i = 0; i < triangleCount; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];
		
		const D3DXVECTOR3& pos0 = positions[index0];
		const D3DXVECTOR3& pos1 = positions[index1];
		const D3DXVECTOR3& pos2 = positions[index2];

		const D3DXVECTOR2& uv0 = uvs[index0];
		const D3DXVECTOR2& uv1 = uvs[index1];
		const D3DXVECTOR2& uv2 = uvs[index2];

		const D3DXVECTOR3& e0 = pos1 - pos0;
		const D3DXVECTOR3& e1 = pos2 - pos0;
		
		const float u0 = uv1.x - uv0.x;
		const float u1 = uv2.x - uv0.x;
		const float v0 = uv1.y - uv0.y;
		const float v1 = uv2.y - uv0.y;
		
		float r = 1.0f / (u0 * v1 - v0 * u1);

		float Tx = r * (v1 * e0.x - v0 * e1.x);
		float Ty = r * (v1 * e0.y - v0 * e1.y);
		float Tz = r * (v1 * e0.z - v0 * e1.z);
		D3DXVECTOR3 tangent(Tx, Ty, Tz);

		float Bx = r * (-u1 * e0.x + u0 * e1.x);
		float By = r * (-u1 * e0.y + u0 * e1.y);
		float Bz = r * (-u1 * e0.z + u0 * e1.z);
		D3DXVECTOR3 binormal(Bx, By, Bz);

		tempTangents[index0] += tangent;
		tempTangents[index1] += tangent;
		tempTangents[index2] += tangent;

		tempBinormals[index0] += binormal;
		tempBinormals[index1] += binormal;
		tempBinormals[index2] += binormal;
	}

	for (UINT i = 0; i < vertexCount; i++)
	{
		const D3DXVECTOR3& n = normals[i];
		const D3DXVECTOR3& t = tempTangents[i];

		// Gram-Schmidt 직교, 정규화
		tempTangents[i] = (t - n * D3DXVec3Dot(&n, &t));
		D3DXVec3Normalize(&(tempTangents[i]), &(tempTangents[i]));

		// Draw방향에 따른 w값 할당
		/*D3DXVECTOR3 tempCross;
		D3DXVec3Cross(&tempCross, &n, &t);
		float w = (D3DXVec3Dot(&tempCross, &tempBinormals[i]) < 0.0f) ? -1.0f : 1.0F;
		tangents[i] = D3DXVECTOR4(tempTangents[i], w);*/

		tangents[i] = tempTangents[i];
	}

	SAFE_DELETE_ARRAY(tempTangents);
	SAFE_DELETE_ARRAY(tempBinormals);
}
