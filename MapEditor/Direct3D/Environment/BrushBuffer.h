#pragma once
#include "../Shaders/ShaderBuffer.h"

class BrushBuffer : public ShaderBuffer
{
public:
	BrushBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.pickPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		data.brushSize = 0.0f;
		data.brushShape = 0.0f;
		data.padding = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	struct Data
	{
		D3DXVECTOR3 pickPosition; 
		float brushSize; 
		float brushShape;
		D3DXVECTOR3 padding;
	};

	Data GetData()
	{
		return data;
	}

	void SetPickPosition(D3DXVECTOR3& position)
	{
		data.pickPosition = position;
	}

	void SetBrushSize(float size)
	{
		data.brushSize = size;
	}

	void SetBrushShaper(float shape)
	{
		data.brushShape = shape;
	}

private:
	Data data;
};