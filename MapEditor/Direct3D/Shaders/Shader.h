#pragma once
#include "SunBuffer.h"

class Shader
{
public:
	Shader(wstring file);
	~Shader();

	static void Create();
	static void Delete();

	void Render();

	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);

private:
	void CreateVertexShader();
	void CreatePixelShader();
	void CheckShaderError(HRESULT hr, ID3D10Blob* error);

	static SunBuffer* sunBuffer;
	
	wstring file;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;

	ID3D11InputLayout* layout;

	ID3D10Blob* vertexBlob;
	ID3D10Blob* pixelBlob;
};