#pragma once
#include "../Shaders/ShaderBuffer.h"

class TerrainBuffer : public ShaderBuffer
{
public:
	TerrainBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		data.ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	}

	struct Data
	{
		D3DXCOLOR diffuse;
		D3DXCOLOR ambient;
	};

	Data GetData()
	{
		return data;
	}

	void SetDiffuseColor(D3DXCOLOR diffuse)
	{
		data.diffuse = diffuse;
	}

	void SetAmbientColor(D3DXCOLOR ambient)
	{
		data.ambient = ambient;
	}

private:
	Data data;
};
