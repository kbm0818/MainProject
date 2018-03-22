#pragma once
#include "../Shaders/Shader.h"
#include "BinaryInputOutputHandler.h"

class Converter;
class ConverterMaterial;
class ConverterBoneWeights;
class ConverterBuffer;
class ConverterPart : public Shader, public BinaryInputOutputHandler
{
public:
	ConverterPart(Converter* Converter);
	ConverterPart(Converter* Converter, ConverterMaterial* material);
	ConverterPart(ConverterPart& otherConverter);
	~ConverterPart();

	void SetConverter(Converter* Converter) { this->Converter = Converter; }

	//void SetConverterBuffer(ConverterBuffer* ConverterBuffer) { this->ConverterBuffer = ConverterBuffer; }
	void AddVertex(D3DXVECTOR3& position, D3DXVECTOR3& normal, D3DXVECTOR2& uv, const ConverterBoneWeights& boneWeights);
	void CreateData();
	void CreateBuffer();

	ConverterMaterial* GetMaterial() { return material; }
	void SetMaterial(ConverterMaterial* material) { this->material = material; }

	void Export(BinaryWriter* bw);
	void Import(BinaryReader* br);

private:
	void CalculateTangents();

	Converter* Converter;

	bool isSkinnedConverter;

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR3> tangents;
	vector<D3DXVECTOR2> uvs;
	vector<UINT> indices;
	vector<ConverterBoneWeights> boneWeights;

	ConverterMaterial* material;
	UINT materialIndex;

	UINT vertexCount;
	VertexTextureNormalTangentBlend* vertex;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* index;
	ID3D11Buffer* indexBuffer;

};