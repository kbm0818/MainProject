#pragma once

class TerrainBuffer : public ShaderBuffer
{
public:
	TerrainBuffer() : ShaderBuffer(&Data, sizeof(Struct))
	{
		Data.cameraPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Data.padding = 0.0f;
	}

	void SetCameraPosition(D3DXVECTOR3 position)
	{
		Data.cameraPosition = position;
	}

	struct Struct
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	Struct Data;
};

struct ExecuteValues;
class Terrain
{
public:
	Terrain();
	~Terrain();

	void Update(ExecuteValues* exValue);
	void Render();
	void PostRender();
	
private:
	void GenerateTerrain();

	void LoadHeightMap();
	void CreateData();
	void CreateBuffer();

private:
	const float TileSize;
	const UINT TileSell;
	typedef Vertex VertexType;

	wstring heightMapFile;

	VertexType* vertexData;
	vector<UINT> indexData;

	UINT vertexCount, indexCount;

	UINT width, height;

	ID3D11Buffer *vertexBuffer, *indexBuffer;

	WorldBuffer* worldBuffer;
	TerrainBuffer* terrainBuffer;

	D3DXMATRIX world;
	Shader* shader;

	ID3D11RasterizerState* wireframeState;
	ID3D11SamplerState* sampler;
};