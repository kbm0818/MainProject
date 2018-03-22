#pragma once
#include "../Shaders/ShaderBuffer.h"

class ModelBuffer : public ShaderBuffer
{
public:
	ModelBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.ambient = D3DXCOLOR(0, 0, 0, 1);
		data.diffuse = D3DXCOLOR(0, 0, 0, 1);
	}

	void SetAmbientColor(D3DXCOLOR& ambient)
	{
		data.ambient = ambient;
	}

	void SetDiffuseColor(D3DXCOLOR& diffuse)
	{
		data.diffuse = diffuse;
	}

	struct Data
	{
		D3DXCOLOR ambient;
		D3DXCOLOR diffuse;
	};

private:
	Data data;
};