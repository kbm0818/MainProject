#include "stdafx.h"
#include "Sky.h"
#include "../Utilities/Mesh.h"

Sky::Sky()
	: meshFile(Contents + L"Meshes/Sphere.data")
	, shaderFile(Shaders + L"Sky.hlsl")
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
	worldBuffer = new WorldBuffer();

	shader = new Shader(shaderFile, ShaderType::VP);
	
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

	SAFE_DELETE(worldBuffer);
	SAFE_DELETE(skyBuffer);
	SAFE_DELETE(shader);
}

void Sky::Update(Camera* camera)
{
	D3DXVECTOR3 position;
	camera->GetPosition(&position);

	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
	worldBuffer->SetMatrix(world);
}

void Sky::Render()
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	worldBuffer->SetVSBuffer(1);
	skyBuffer->SetPSBuffer(1);
	shader->Render(ShaderType::VP);


	States::SetDepthStencil(depthOffState);
	States::SetRasterizer(countClockState);
	{
		D3D::GetDC()->DrawIndexed(indexCount, 0, 0);
	}
	States::SetRasterizer(clockState);;
	States::SetDepthStencil(depthOnState);
}

void Sky::PostRender()
{
	ImGui::Begin("Environment");

	if (ImGui::CollapsingHeader("Sky"))
	{
		ImGui::ColorEdit3("Center", (float *)&skyBuffer->Data.Center);
		ImGui::ColorEdit3("Apex", (float *)&skyBuffer->Data.Apex);
	}

	ImGui::End();
}
