#pragma once

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Open(wstring filePath);

	void CopyVertex(Vertex** vertex, UINT* count);
	void CopyVertex(VertexTexture** vertex, UINT* count);
	void CopyVertex(VertexColor** vertex, UINT* count, const D3DXCOLOR& color);
	void CopyVertex(VertexColorNormal** vertex, UINT* count, const D3DXCOLOR& color);
	void CopyVertex(VertexTextureNormal** vertex, UINT* count);
	void CopyIndex(UINT** index, UINT* count);

private:
	VertexTextureNormal* vertexData;
	UINT vertexCount;

	UINT* indexData;
	UINT indexCount;
};