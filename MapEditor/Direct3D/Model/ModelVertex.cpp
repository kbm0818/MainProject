#include "../stdafx.h"
#include "ModelVertex.h"
#include "Model.h"
#include "ModelBuffer.h"
#include "ModelMaterial.h"

ModelVertex::ModelVertex(Model * model, ModelMaterial * material, Shader * shader, ModelBuffer * buffer)
	: model(model), material(material), shader(shader), buffer(buffer)
{
	if (material != nullptr)
		materialIndex = material->GetIndex();
	else
		materialIndex = -1;
}

ModelVertex::ModelVertex(Model * model, Shader * shader, ModelBuffer * buffer)
	: vertexData(nullptr), indexData(nullptr)
	, vertexBuffer(nullptr), indexBuffer(nullptr)
	, model(model), shader(shader), buffer(buffer)
{
}

ModelVertex::~ModelVertex()
{
	SAFE_DELETE_ARRAY(vertexData);
	SAFE_DELETE_ARRAY(indexData);

	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}

void ModelVertex::CreateBuffer()
{
	vertexCount = positions.size();
	indexCount = indices.size();

	vertexData = new VertexTextureNormal[vertexCount];
	for (UINT i = 0; i < vertexCount; i++)
	{
		vertexData[i].position = positions[i];
		vertexData[i].normal = normals[i];
		vertexData[i].uv = uvs[i];
	}

	indexData = new UINT[indexCount];
	for (UINT i = 0; i < indexCount; i++)
		indexData[i] = indices[i];


	HRESULT hr;
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA data;


	//1. Vertex Buffer
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(VertexTextureNormal) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertexData;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));


	//2. Index Buffer
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = indexData;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
	assert(SUCCEEDED(hr));
}

void ModelVertex::PushVertex(D3DXVECTOR3 & position, D3DXVECTOR3 & normal, D3DXVECTOR2 & uv)
{
	positions.push_back(position);
	normals.push_back(normal);
	uvs.push_back(uv);

	indices.push_back((UINT)indices.size());
}

void ModelVertex::Update()
{
}

void ModelVertex::Render(Camera* camera)
{
	ID3D11DeviceContext* dc = D3D::GetDC();

	UINT stride = sizeof(VertexTextureNormal);
	UINT offset = 0;

	dc->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	dc->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DXCOLOR ambient = D3DXCOLOR(1, 1, 1, 1);
	D3DXCOLOR diffuse = D3DXCOLOR(0, 0, 0, 1);
	if (material != NULL)
	{
		ambient = material->GetAmbientColor();
		diffuse = material->GetDiffuseColor();

		ID3D11ShaderResourceView* diffuseView = material->GetDiffuseView();
		dc->PSSetShaderResources(0, 1, &diffuseView);
	}
	buffer->SetAmbientColor(ambient);
	buffer->SetDiffuseColor(diffuse);
	buffer->SetPSBuffer(1);


	D3DXMATRIX world = model->GetGeometricOffset();
	camera->SetVSBuffer(&world);
	
	shader->Render();

	dc->DrawIndexed(indexCount, 0, 0);
}

void ModelVertex::SaveBinary(BinaryWriter * writer)
{
	writer->Write(materialIndex);

	writer->Write(vertexCount);
	writer->Write(vertexData, sizeof(VertexTextureNormal), vertexCount);

	writer->Write(indexCount);
	writer->Write(indexData, sizeof(UINT), indexCount);
}

void ModelVertex::OpenBinary(BinaryReader * reader)
{
	materialIndex = reader->UInt();

	vertexCount = reader->UInt();
	SAFE_DELETE_ARRAY(vertexData);
	vertexData = new VertexTextureNormal[vertexCount];
	reader->Read(vertexData, sizeof(VertexTextureNormal), vertexCount);

	indexCount = reader->UInt();
	SAFE_DELETE_ARRAY(indexData);
	indexData = new UINT[indexCount];
	reader->Read(indexData, sizeof(UINT), indexCount);

	if(materialIndex != -1)
		material = model->GetMaterial(materialIndex);

	HRESULT hr;
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA data;

	//1. Vertex Buffer
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(VertexTextureNormal) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertexData;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));


	//2. Index Buffer
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = indexData;

	hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
	assert(SUCCEEDED(hr));
}
