#include "../stdafx.h"
#include "Sky.h"
#include "SkyBuffer.h"
#include "../Utilities/Mesh.h"

Sky::Sky()
	: meshFile(Contents + L"Meshes/Sphere.data")
	, shader(NULL)
{
	VertexType* vertex = NULL;
	UINT* index = NULL;

	Mesh mesh;
	mesh.Open(meshFile);
	mesh.CopyVertex(&vertex, &vertexCount);
	mesh.CopyIndex(&index, &indexCount);
	
	
	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(VertexType) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = vertex;

	HRESULT hr;
	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));


	desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	data = { 0 };
	data.pSysMem = index;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
	assert(SUCCEEDED(hr));

	SAFE_DELETE_ARRAY(vertex);
	SAFE_DELETE_ARRAY(index);

	D3DXMatrixIdentity(&world);
	
	skyBuffer = new SkyBuffer();

	
	D3D11_RASTERIZER_DESC rasterizerDesc;
	States::GetRasterizerDesc(&rasterizerDesc);
	rasterizerDesc.FrontCounterClockwise = false;
	States::CreateRasterizer(&rasterizerDesc, &clockState);

	States::GetRasterizerDesc(&rasterizerDesc);
	rasterizerDesc.FrontCounterClockwise = true;
	States::CreateRasterizer(&rasterizerDesc, &countClockState);

	D3D11_DEPTH_STENCIL_DESC depthDesc;
	States::GetDepthStencilDesc(&depthDesc);
	depthDesc.DepthEnable = true;
	States::CreateDepthStencil(&depthDesc, &depthOnState);

	States::GetDepthStencilDesc(&depthDesc);
	depthDesc.DepthEnable = false;
	States::CreateDepthStencil(&depthDesc, &depthOffState);
}

Sky::~Sky()
{
	SAFE_RELEASE(depthOnState);
	SAFE_RELEASE(depthOffState);
	SAFE_RELEASE(clockState);
	SAFE_RELEASE(countClockState);

	SAFE_DELETE(skyBuffer);
	SAFE_DELETE(shader);
}

void Sky::Update(Camera* camera)
{
	if (shader == NULL) return;

	D3DXVECTOR3 position;
	camera->GetPosition(&position);
	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
}

void Sky::Render(Camera* camera)
{
	if (shader == NULL) return;

	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	camera->SetVSBuffer(&world);
	skyBuffer->SetPSBuffer(1);
	shader->Render();


	States::SetDepthStencil(depthOffState);
	States::SetRasterizer(countClockState);
	{
		D3D::GetDC()->DrawIndexed(indexCount, 0, 0);
	}
	States::SetRasterizer(clockState);;
	States::SetDepthStencil(depthOnState);
}

void Sky::SetShader(wstring file)
{
	SAFE_DELETE(shader);

	shader = new Shader(file);
	shader->CreateInputLayout(VertexType::desc, VertexType::count);
}

void Sky::SetSkyBufferCenter(int center)
{
	skyBuffer->SetCenter(center);
}

void Sky::SetSkyBufferApex(int apex)
{
	skyBuffer->SetApex(apex);
}
