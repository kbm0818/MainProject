#pragma once
#include "../Shaders/Shader.h"
#include "BinaryInputOutputHandler.h"

class Model;
class ModelMaterial;
class ModelBoneWeights;
class ModelBuffer;
class ModelPart : public Shader, public BinaryInputOutputHandler
{
public:
	ModelPart(Model* model);
	ModelPart(Model* model, ModelMaterial* material);
	ModelPart(ModelPart& otherModel);
	~ModelPart();

	void Update(bool isAnimation);
	void Render();

	void SetModel(Model* model) { this->model = model; }

	//void SetModelBuffer(ModelBuffer* modelBuffer) { this->modelBuffer = modelBuffer; }
	void AddVertex(D3DXVECTOR3& position, D3DXVECTOR3& normal, D3DXVECTOR2& uv, const ModelBoneWeights& boneWeights);
	void CreateData();
	void CreateBuffer();

	ModelMaterial* GetMaterial() { return material; }
	void SetMaterial(ModelMaterial* material) { this->material = material; }

	void Export(BinaryWriter* bw);
	void Import(BinaryReader* br);

private:
	void CalculateTangents();

	Model* model;

	bool isSkinnedModel;

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR3> tangents;
	vector<D3DXVECTOR2> uvs;
	vector<UINT> indices;
	vector<ModelBoneWeights> boneWeights;

	ModelMaterial* material;
	UINT materialIndex;

	UINT vertexCount;
	VertexTextureNormalTangentBlend* vertex;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* index;
	ID3D11Buffer* indexBuffer;

};