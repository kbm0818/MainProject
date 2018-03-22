#pragma once

class Brush;
class TerrainBuffer;
class Terrain
{
public:
	Terrain();
	~Terrain();

	void Update(Camera* camera);
	void Render(Camera* camera);

	void SetShader(wstring file);

	UINT GetWidth();
	UINT GetHeight();
	void SetWidth(UINT width);
	void SetHeight(UINT height);
	void SetSize(UINT width, UINT height);

	UINT GetDiffuseColor();
	UINT GetAmbientColor();
	void SetDiffuseColor(int diffuse);
	void SetAmbientColor(int ambient);

	void SetDiffuseFile(wstring file);
	void SetStage1File(wstring file);
	void SetStage2File(wstring file);
	void SetStage3File(wstring file);
	void SetStage4File(wstring file);

	Brush* GetBrush();

private:
	void CreateVertexData();
	void CreateIndexData();
	void CalcNormalVector();
	void CreateBuffer();
	void CreateSRV();
	void CreateSRV(wstring file, ID3D11ShaderResourceView** view);

private:
	Brush* brush;
	friend class Brush;

private:
	UINT width, height;

	typedef VertexColorTexture2Normal VertexType;
	VertexType* vertexData;
	UINT* indexData;

	wstring diffuseMapFile; // 기본 지형색상 텍스쳐
	ID3D11ShaderResourceView* diffuseMap;
	wstring stage1MapFile; // 스플래팅용 텍스쳐
	ID3D11ShaderResourceView* stage1Map;
	wstring stage2MapFile;
	ID3D11ShaderResourceView* stage2Map;
	wstring stage3MapFile;
	ID3D11ShaderResourceView* stage3Map;
	wstring stage4MapFile;
	ID3D11ShaderResourceView* stage4Map;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	UINT vertexCount;
	UINT indexCount;

	Shader* shader;
	TerrainBuffer* terrainBuffer;

	D3DXMATRIX world;
};