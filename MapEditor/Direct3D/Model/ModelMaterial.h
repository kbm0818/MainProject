#pragma once

class BinaryWriter;
class BinaryReader;
class ModelMaterial
{
public:
	ModelMaterial(int number, FbxSurfaceMaterial* material);
	ModelMaterial();
	~ModelMaterial();

	UINT GetIndex() { return number; }

	D3DXCOLOR GetAmbientColor() { return ambient; }
	D3DXCOLOR GetDiffuseColor() { return diffuse; }

	ID3D11ShaderResourceView* GetDiffuseView()
	{
		return diffuseView;
	}

	void CreateView(string path, ID3D11ShaderResourceView** view);

	void OpenBinary(BinaryReader* reader);
	void SaveBinary(BinaryWriter* writer);

private:
	D3DXCOLOR GetProperty
	(
		FbxSurfaceMaterial* material
		, const char* name, const char* factorName
		, string* textureName
	);

	void GetProperty
	(
		FbxSurfaceMaterial* material
		, const char* name
		, string* textureName
	);

	UINT number;

	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR specular;
	D3DXCOLOR emissive;
	float shininess;

	string ambientFile;
	string diffuseFile;
	string specularFile;
	string emissiveFile;
	string normalMapFile;

	ID3D11ShaderResourceView* ambientView;
	ID3D11ShaderResourceView* diffuseView;
	ID3D11ShaderResourceView* specularView;
	ID3D11ShaderResourceView* emissiveView;
	ID3D11ShaderResourceView* normalMapView;
};