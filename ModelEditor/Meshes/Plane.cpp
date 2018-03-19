#include "stdafx.h"
#include "Plane.h"
#include "../Utilities/Mesh.h"

Plane::Plane()
{
	wstring file = Shaders + L"PlaneColor.hlsl";
	shader = new Shader(file);

	worldBuffer = new WorldBuffer();
	planeBuffer = new PlaneBuffer();

	VertexType* vertex = NULL;
	UINT* index = NULL;

	file = Contents + L"Meshes/Quad.data";
	Mesh* mesh = new Mesh();
	{
		mesh->Open(file);
		mesh->CopyVertex(&vertex, &vertexCount);
		mesh->CopyIndex(&index, &indexCount);
	}
	SAFE_DELETE(mesh);
	

	HRESULT hr;

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(VertexType) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = vertex;

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

	
	D3DXMATRIX S, R;
	D3DXMatrixScaling(&S, 50, 50, 1);
	D3DXMatrixRotationX(&R, 90 * (float)D3DX_PI / 180);
	world = S * R;
}

Plane::~Plane()
{
	SAFE_DELETE(worldBuffer);
	SAFE_DELETE(shader);

	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}

void Plane::Update()
{
	worldBuffer->SetMatrix(world);
}

void Plane::Render()
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	planeBuffer->SetPSBuffer(1);
	worldBuffer->SetVSBuffer(1);	

	shader->Render();

	D3D::GetDC()->DrawIndexed(indexCount, 0, 0);
}

void Plane::PostRender()
{
	ImGui::Begin("Environment");
	if (ImGui::CollapsingHeader("Plane"))
	{
		ImGui::ColorEdit3("Color", (float *)&planeBuffer->Data.Color);
	}
	ImGui::End();
}
