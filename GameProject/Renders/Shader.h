#pragma once

enum class ShaderType
{
	VP, VHDP,
};

class Shader
{
public:
	Shader(wstring shaderFile, ShaderType type);
	~Shader();

	void Render(ShaderType type);

private:
	void CreateVertexShader();
	void CreatePixelShader();
	void CreateHullShader();
	void CreateDomainShader();

	void CheckShaderError(HRESULT hr, ID3DBlob* error);
	void CreateInputLayout();

private:
	wstring shaderFile;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11HullShader* hullShader;
	ID3D11DomainShader* domainShader;

	ID3D11InputLayout* inputLayout;

	ID3DBlob* vertexBlob;
	ID3DBlob* pixelBlob;
	ID3D10Blob* hullBlob;
	ID3D10Blob* domainBlob;

	ID3D11ShaderReflection* reflection;
};