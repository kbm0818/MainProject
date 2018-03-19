#pragma once

class SkyBuffer : public ShaderBuffer
{
public:
	SkyBuffer() : ShaderBuffer(&Data, sizeof(Struct))
	{
		Data.Apex = D3DXCOLOR(0.0f, 0.05f, 0.6f, 1.0f);
		Data.Center = D3DXCOLOR(0.0f, 0.5f, 0.8f, 1.0f);
	}

	struct Struct
	{
		D3DXCOLOR Center;
		D3DXCOLOR Apex;
	};

	Struct Data;
};

class Sky
{
public:
	Sky();
	~Sky();

	void Update(Camera* camera);
	void Render();
	void PostRender();

private:
	typedef Vertex VertexType;

	wstring meshFile;
	wstring shaderFile;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	UINT vertexCount;
	UINT indexCount;

	Shader* shader;
	SkyBuffer* skyBuffer;
	WorldBuffer* worldBuffer;

	D3DXMATRIX world;

	ID3D11RasterizerState* clockState;
	ID3D11RasterizerState* countClockState;
	ID3D11DepthStencilState* depthOnState;
	ID3D11DepthStencilState* depthOffState;
};