#pragma once
#include "../Shaders/ShaderBuffer.h"

class GridBuffer : public ShaderBuffer
{
public:
	GridBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.thickness = 1.0f;
		data.gridSpace = 1.0f;
		data.padding = D3DXVECTOR2(0.0f, 0.0f);
	}

	struct Data
	{
		float thickness;
		float gridSpace;
		D3DXVECTOR2 padding;
	};

	Data GetData()
	{
		return data;
	}

	void SetThickness(float value)
	{
		data.thickness = value;
	}

	void SetGridSpace(float value)
	{
		data.gridSpace = value;
	}

private:
	Data data;
};