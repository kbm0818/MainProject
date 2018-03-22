#pragma once

class Model;
class FbxLoader
{
public:
	static void Create(string file, Model** model);

	static void SaveBinary(wstring fileFullPath, Model** model);
	static void OpenBinary(wstring fileFullPath, Model** model);

private:
	FbxLoader();
	~FbxLoader();
	
	Model* Open(string file);

	void ProcessMaterial();
	void ProcessNode(FbxNode* node, FbxNodeAttribute::EType type);
	void ProcessMesh(FbxNode* node);

	ModelMaterial* LinkMaterialWithPolygon
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

	ModelMaterial* GetMaterial(FbxSurfaceMaterial* fbxMaterial);
	D3DXMATRIX GetGeometricOffset(FbxNode* node);

	Model* model;

	FbxManager* manager;
	FbxScene* scene;
	FbxImporter* importer;
	FbxGeometryConverter* converter;

	vector<FbxSurfaceMaterial *> materials;
};
