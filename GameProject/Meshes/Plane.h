#pragma once

class PlaneBuffer : public ShaderBuffer
{
public:
	PlaneBuffer() : ShaderBuffer(&Data, sizeof(Struct))
	{
		Data.Color = D3DXCOLOR(0.0f, 0.05f, 0.6f, 1.0f);
	}

	struct Struct
	{
		D3DXCOLOR Color;
	};

	Struct Data;
};

class Plane
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();
	void PostRender();

private:
	typedef Vertex VertexType;

	Shader* shader;
	PlaneBuffer* planeBuffer;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	UINT vertexCount;
	UINT indexCount;

	D3DXMATRIX world;
	WorldBuffer* worldBuffer;
};