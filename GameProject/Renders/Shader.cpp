#include "stdafx.h"
#include "Shader.h"

void Shader::Render(ShaderType type)
{
	switch (type)
	{
	case ShaderType::VP:
		D3D::GetDC()->IASetInputLayout(inputLayout);
		D3D::GetDC()->VSSetShader(vertexShader, NULL, 0);
		D3D::GetDC()->HSSetShader(nullptr, NULL, 0);
		D3D::GetDC()->DSSetShader(nullptr, NULL, 0);
		D3D::GetDC()->PSSetShader(pixelShader, NULL, 0);
		break;

	case ShaderType::VHDP:
		D3D::GetDC()->IASetInputLayout(inputLayout);
		D3D::GetDC()->VSSetShader(vertexShader, NULL, 0);
		D3D::GetDC()->HSSetShader(hullShader, NULL, 0);
		D3D::GetDC()->DSSetShader(domainShader, NULL, 0);
		D3D::GetDC()->PSSetShader(pixelShader, NULL, 0);
		break;
	}
}

Shader::Shader(wstring shaderFile, ShaderType type)
	: shaderFile(shaderFile)
	, pixelBlob(nullptr), vertexBlob(nullptr)
	, pixelShader(nullptr), vertexShader(nullptr)
	, hullBlob(nullptr), domainBlob(nullptr)
	, hullShader(nullptr), domainShader(nullptr)
{
	switch (type)
	{
	case ShaderType::VP:
		CreateVertexShader();
		CreatePixelShader();
		break;
	case ShaderType::VHDP:
		CreateVertexShader();
		CreateHullShader();
		CreateDomainShader();
		CreatePixelShader();
		break;
	}

	CreateInputLayout();
}

Shader::~Shader()
{
	SAFE_RELEASE(reflection);

	SAFE_RELEASE(inputLayout);

	SAFE_RELEASE(domainBlob);
	SAFE_RELEASE(domainShader);

	SAFE_RELEASE(hullBlob);
	SAFE_RELEASE(hullShader);

	SAFE_RELEASE(vertexBlob);
	SAFE_RELEASE(vertexShader);

	SAFE_RELEASE(pixelBlob);
	SAFE_RELEASE(pixelShader);
}

void Shader::CreateVertexShader()
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile
	(
		shaderFile.c_str(), NULL, NULL, "VS", "vs_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL
		, &vertexBlob, &error, NULL
	);
	CheckShaderError(hr, error);

	hr = D3D::GetDevice()->CreateVertexShader
	(
		vertexBlob->GetBufferPointer()
		, vertexBlob->GetBufferSize()
		, NULL
		, &vertexShader
	);
	assert(SUCCEEDED(hr));
}

void Shader::CreatePixelShader()
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile
	(
		shaderFile.c_str(), NULL, NULL, "PS", "ps_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL
		, &pixelBlob, &error, NULL
	);
	CheckShaderError(hr, error);

	hr = D3D::GetDevice()->CreatePixelShader
	(
		pixelBlob->GetBufferPointer()
		, pixelBlob->GetBufferSize()
		, NULL
		, &pixelShader
	);
	assert(SUCCEEDED(hr));
}

void Shader::CreateHullShader()
{
	ID3D10Blob* error;
	HRESULT hr = D3DX10CompileFromFile
	(
		shaderFile.c_str(), NULL, NULL, "HS", "hs_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL
		, &hullBlob, &error, NULL
	);
	CheckShaderError(hr, error);

	hr = D3D::GetDevice()->CreateHullShader
	(
		hullBlob->GetBufferPointer()
		, hullBlob->GetBufferSize()
		, NULL
		, &hullShader
	);
	assert(SUCCEEDED(hr));
}

void Shader::CreateDomainShader()
{
	ID3D10Blob* error;
	HRESULT hr = D3DX10CompileFromFile
	(
		shaderFile.c_str(), NULL, NULL, "DS", "ds_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL
		, &domainBlob, &error, NULL
	);
	CheckShaderError(hr, error);

	hr = D3D::GetDevice()->CreateDomainShader
	(
		domainBlob->GetBufferPointer()
		, domainBlob->GetBufferSize()
		, NULL
		, &domainShader
	);
	assert(SUCCEEDED(hr));
}

void Shader::CheckShaderError(HRESULT hr, ID3DBlob * error)
{
	if (FAILED(hr))
	{
		if (error != NULL)
		{
			string str = (const char *)error->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "Shader Error", MB_OK);
		}
		assert(false);
	}
}

void Shader::CreateInputLayout()
{
	HRESULT hr;
	hr = D3DReflect
	(
		vertexBlob->GetBufferPointer()
		, vertexBlob->GetBufferSize()
		, IID_ID3D11ShaderReflection
		, (void**)&reflection
	);
	assert(SUCCEEDED(hr));

	D3D11_SHADER_DESC shaderDesc;
	reflection->GetDesc(&shaderDesc);

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (UINT i = 0; i< shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		reflection->GetInputParameterDesc(i, &paramDesc);

		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		string temp = paramDesc.SemanticName;
		if (temp == "POSITION")
			elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

		inputLayoutDesc.push_back(elementDesc);
	}

	hr = D3D::GetDevice()->CreateInputLayout
	(
		&inputLayoutDesc[0]
		, inputLayoutDesc.size()
		, vertexBlob->GetBufferPointer()
		, vertexBlob->GetBufferSize()
		, &inputLayout
	);
	assert(SUCCEEDED(hr));
}
