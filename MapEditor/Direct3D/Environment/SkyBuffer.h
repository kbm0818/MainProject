#pragma once
#include "../Shaders/ShaderBuffer.h"

class SkyBuffer : public ShaderBuffer
{
public:
	SkyBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.apex = D3DXCOLOR(0.0f, 0.05f, 0.6f, 1.0f);
		data.center = D3DXCOLOR(0.0f, 0.5f, 0.8f, 1.0f);
	}

	struct Data
	{
		D3DXCOLOR center;
		D3DXCOLOR apex;
	};
	
	void SetApex(int apex)
	{
		data.apex = D3DXCOLOR(apex);
	}
	void SetCenter(int center)
	{
		data.center = D3DXCOLOR(center);
	}

private:
	Data data;
};
