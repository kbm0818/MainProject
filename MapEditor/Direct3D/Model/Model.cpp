#include "../stdafx.h"
#include "Model.h"
#include "ModelMaterial.h"
#include "ModelVertex.h"
#include "ModelBuffer.h"
#include "../Utilities/String.h"

Model::Model(wstring name)
	: name(name)
	, translate(D3DXVECTOR3(0.0f,0.0f,0.0f)), rotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
{
	TRSUpdate();

	shader = new Shader(L"../Direct3D/Model/Model.hlsl");
	shader->CreateInputLayout(VertexTextureNormal::desc, VertexTextureNormal::count);

	buffer = new ModelBuffer();
}

Model::Model()
{
	D3DXMatrixIdentity(&geometricOffset);

	shader = new Shader(L"../Direct3D/Model/Model.hlsl");
	shader->CreateInputLayout(VertexTextureNormal::desc, VertexTextureNormal::count);

	buffer = new ModelBuffer();
}

Model::~Model()
{
	SAFE_DELETE(buffer);
	SAFE_DELETE(shader);

	for (ModelVertex* vertex : vertices)
		SAFE_DELETE(vertex);

	for (ModelMaterial* material : materials)
		SAFE_DELETE(material);
}

void Model::PushMaterial(ModelMaterial * material)
{
	materials.push_back(material);
}

void Model::PushVertex(ModelMaterial * material, D3DXVECTOR3 & position, D3DXVECTOR3 & normal, D3DXVECTOR2 & uv)
{
	bool isNew = true;

	ModelVertex* vertex = NULL;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertex = vertices[i];

		if (material == vertex->GetMaterial())
		{
			vertex->PushVertex(position, normal, uv);
			isNew = false;
		}
	}

	if (isNew == true)
	{
		vertex = new ModelVertex(this, material, shader, buffer);
		vertex->PushVertex(position, normal, uv);

		vertices.push_back(vertex);
	}
}

void Model::CreateBuffer()
{
	for (ModelVertex* vertex : vertices)
		vertex->CreateBuffer();
}

void Model::Update()
{
	for (ModelVertex* vertex : vertices)
		vertex->Update();
}

void Model::Render(Camera * camera)
{
	for (ModelVertex* vertex : vertices)
		vertex->Render(camera);
}

void Model::SaveBinary(BinaryWriter* writer)
{
	writer->Write((UINT)(materials.size()));
	for (size_t i = 0; i < materials.size(); i++)
		materials[i]->SaveBinary(writer);

	writer->Write((UINT)(vertices.size()));
	for (size_t i = 0; i < vertices.size(); i++)
		vertices[i]->SaveBinary(writer);
}

void Model::OpenBinary(BinaryReader * reader)
{
	UINT materialsCount = reader->UInt();
	materials.clear();
	materials.reserve(materialsCount);
	
	for (size_t i = 0; i < materialsCount; i++)
	{
		ModelMaterial* material = new ModelMaterial();
		material->OpenBinary(reader);
		materials.push_back(material);
	}

	UINT modelVertexCount = reader->UInt();
	vertices.clear();
	vertices.reserve(modelVertexCount);

	for (size_t i = 0; i < modelVertexCount; i++)
	{
		ModelVertex* modelVertex = new ModelVertex(this, shader, buffer);
		modelVertex->OpenBinary(reader);
		vertices.push_back(modelVertex);
	}
}

string Model::GetStringName()
{
	return String::WStringToString(name);
}

void Model::SetTranslate(D3DXVECTOR3 trans)
{
	this->translate = trans;
	TRSUpdate();
}

void Model::TRSUpdate()
{
	D3DXMatrixTranslation(&T, translate.x, translate.y, translate.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotate.x, rotate.y, rotate.z);
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);

	geometricOffset = S * T;
}
