#include "../stdafx.h"
#include "Terrain.h"
#include "Renders/Shader.h"
#include "./Executes/Execute.h"

Terrain::Terrain()
	: width(0), height(0)
	, vertexData(nullptr)
	, vertexCount(0), indexCount(0)
	, vertexBuffer(nullptr), indexBuffer(nullptr)
	, TileSize(1.0f), TileSell(8)
	, heightMapFile(Textures + L"heightmap.bmp")
{
	GenerateTerrain();

	shader = new Shader(Shaders + L"TesTerrain.hlsl", ShaderType::VHDP);
	worldBuffer = new WorldBuffer();	
	terrainBuffer = new TerrainBuffer();

	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	States::CreateRasterizer(&rasterDesc, &wireframeState);

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	States::CreateSampler(&samplerDesc, &sampler);

	D3DXMatrixIdentity(&world);
}

Terrain::~Terrain()
{
	SAFE_DELETE(terrainBuffer);
	SAFE_DELETE(shader);
	SAFE_DELETE(worldBuffer);

	SAFE_DELETE_ARRAY(vertexData);
	
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}

void Terrain::Update(ExecuteValues* exValue)
{
	exValue->ViewProjection->SetDSBuffer(0);

	D3DXVECTOR3 cameraPosition;
	exValue->MainCamera->GetPosition(&cameraPosition);
	terrainBuffer->SetCameraPosition(cameraPosition);

	worldBuffer->SetMatrix(world);
}

void Terrain::Render()
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	
	worldBuffer->SetDSBuffer(1);

	worldBuffer->SetHSBuffer(1);
	terrainBuffer->SetHSBuffer(2);

	shader->Render(ShaderType::VHDP);
	
	D3D::GetDC()->DSSetSamplers(0, 1, &sampler);

	D3D::GetDC()->RSSetState(wireframeState);

	D3D::GetDC()->DrawIndexed(indexCount, 0, 0);
}

void Terrain::PostRender()
{
}

void Terrain::GenerateTerrain()
{
	LoadHeightMap();
	CreateData();
	CreateBuffer();
}

void Terrain::LoadHeightMap()
{
	ID3D11Texture2D* heightMapTexture;
	Texture::LoadTexture(heightMapFile, &heightMapTexture);

	D3D11_TEXTURE2D_DESC desc;
	heightMapTexture->GetDesc(&desc);

	width = desc.Width;
	height = desc.Height;
}

void Terrain::CreateData()
{
	vertexCount = (width + 1) * (height + 1);

	vertexData = new VertexType[vertexCount];
	for (UINT z = 0; z <= height; z++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			int index = (width + 1) * z + x;

			vertexData[index].position.x = (float)x * width / TileSell;
			vertexData[index].position.y = 0;
			vertexData[index].position.z = (float)z * height / TileSell;

			//vertexData[index].uv.x = (float)(x);// (float)width;
			//vertexData[index].uv.y = (float)(z);// (float)height;

			//vertexData[index].normal = D3DXVECTOR3(0, 0, 0);
		}
	}

	indexCount = width * height * 4;

	UINT count = 0;
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			indexData.push_back((width + 1) * (z + 1) + x);
			indexData.push_back((width + 1) * (z + 1) + (x + 1));

			indexData.push_back((width + 1) * z + x);
			indexData.push_back((width + 1) * z + x + 1);
		}//for(x)
	}//for(z)

	if (indexData.size() != indexCount)
		assert(0);
}

void Terrain::CreateBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth = sizeof(VertexType) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = vertexData;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));


	desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	data = { 0 };
	data.pSysMem = &indexData[0];

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
	assert(SUCCEEDED(hr));
}
