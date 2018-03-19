#include "stdafx.h"
#include "Mesh.h"
#include "BinaryFile.h"

Mesh::Mesh()
	: vertexData(NULL)
	, vertexCount(0)
	, indexData(NULL)
	, indexCount(0)
{
}

Mesh::~Mesh()
{
	SAFE_DELETE_ARRAY(vertexData);
	SAFE_DELETE_ARRAY(indexData);
}

void Mesh::Open(wstring filePath)
{
	BinaryReader reader;
	reader.Open(filePath);

	vertexCount = reader.UInt();
	vertexData = new VertexTextureNormal[vertexCount];
	for (UINT i = 0; i < vertexCount; i++)
	{
		vertexData[i].position = reader.Vector3();
		vertexData[i].uv = reader.Vector2();
		vertexData[i].normal = reader.Vector3();
	}

	indexCount = reader.UInt();
	indexData = new UINT[indexCount];
	for (UINT i = 0; i < indexCount; i++)
		indexData[i] = reader.UInt();

	reader.Close();
}

void Mesh::CopyVertex(Vertex ** vertex, UINT * count)
{
	*count = vertexCount;

	*vertex = new Vertex[vertexCount];
	for (UINT i = 0; i < vertexCount; i++)
		(*vertex)[i].position = vertexData[i].position;
}

void Mesh::CopyVertex(VertexTexture ** vertex, UINT * count)
{
	*count = vertexCount;

	*vertex = new VertexTexture[vertexCount];
	for (UINT i = 0; i < vertexCount; i++)
	{
		(*vertex)[i].position = vertexData[i].position;
		(*vertex)[i].uv = vertexData[i].uv;
	}
}

void Mesh::CopyVertex(VertexColor ** vertex, UINT * count, const D3DXCOLOR & color)
{
	*count = vertexCount;

	*vertex = new VertexColor[vertexCount];
	for (UINT i = 0; i < vertexCount; i++)
	{
		(*vertex)[i].position = vertexData[i].position;
		(*vertex)[i].color = color;
	}
}

void Mesh::CopyVertex(VertexColorNormal ** vertex, UINT * count, const D3DXCOLOR & color)
{
	*count = vertexCount;

	*vertex = new VertexColorNormal[vertexCount];
	for (UINT i = 0; i < vertexCount; i++)
	{
		(*vertex)[i].position = vertexData[i].position;
		(*vertex)[i].normal = vertexData[i].normal;
		(*vertex)[i].color = color;
	}
}

void Mesh::CopyVertex(VertexTextureNormal ** vertex, UINT * count)
{
	*count = vertexCount;

	*vertex = new VertexTextureNormal[vertexCount];
	memcpy(*vertex, vertexData, sizeof(VertexTextureNormal) * vertexCount);
}

void Mesh::CopyIndex(UINT ** index, UINT * count)
{
	*count = indexCount;

	*index = new UINT[indexCount];
	memcpy(*index, indexData, sizeof(UINT) * indexCount);
}
