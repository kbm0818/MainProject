#pragma once

class ModelBuffer;
class ModelVertex;
class ModelMaterial;
class BinaryWriter;
class BinaryReader;
class Model
{
public:
	Model(wstring name);
	Model();
	~Model();

	D3DXMATRIX GetGeometricOffset()
	{
		return geometricOffset;
	}

	void SetGeometricOffset(const D3DXMATRIX& matrix)
	{
		geometricOffset = matrix;
	}

	void PushMaterial(ModelMaterial* material);
	ModelMaterial* GetMaterial(UINT number)
	{
		return materials[number];
	}

	void PushVertex
	(
		ModelMaterial* material
		, D3DXVECTOR3& position
		, D3DXVECTOR3& normal
		, D3DXVECTOR2& uv
	);

	void CreateBuffer();

	void Update();
	void Render(Camera* camera);

	void SaveBinary(BinaryWriter* writer);
	void OpenBinary(BinaryReader* reader);

	string GetStringName();
	D3DXVECTOR3 GetTranslate() { return translate; }
	D3DXVECTOR3 GetRotate() { return rotate; }
	D3DXVECTOR3 GetScale() { return scale; }

	void SetTranslate(D3DXVECTOR3 trans);

private:
	void TRSUpdate();

private:
	wstring name;

	Shader* shader;
	ModelBuffer* buffer;

	D3DXVECTOR3 translate, rotate, scale;
	D3DXMATRIX T, R, S;
	D3DXMATRIX geometricOffset;

	vector<ModelMaterial *> materials;
	vector<ModelVertex *> vertices;
};