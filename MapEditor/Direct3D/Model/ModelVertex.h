#pragma once

class Model;
class ModelBuffer;
class ModelMaterial;
class BinaryReader;
class BinaryWriter;
class ModelVertex
{
public:
	ModelVertex(Model* model, ModelMaterial* material, Shader* shader, ModelBuffer* buffer);
	ModelVertex(Model* model, Shader * shader, ModelBuffer * buffer);

	~ModelVertex();

	void CreateBuffer();

	ModelMaterial* GetMaterial()
	{
		return material;
	}

	void SetMaterial(ModelMaterial* material)
	{
		this->material = material;
	}

	void PushVertex
	(
		D3DXVECTOR3& position
		, D3DXVECTOR3& normal
		, D3DXVECTOR2& uv
	);

	void Update();
	void Render(Camera* camera);

	void SaveBinary(BinaryWriter* writer);
	void OpenBinary(BinaryReader* reader);

private:
	Model* model;
	ModelMaterial* material;
	UINT materialIndex;

	Shader* shader;
	ModelBuffer* buffer;

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> uvs;
	vector<UINT> indices;

	ID3D11Buffer* vertexBuffer, *indexBuffer;
	UINT vertexCount, indexCount;

	VertexTextureNormal* vertexData;
	UINT* indexData;
};