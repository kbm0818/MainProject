#pragma once
#include "ShaderBuffer.h"

class SunBuffer : public ShaderBuffer
{
public:
	SunBuffer()
		: ShaderBuffer(&data, sizeof(Data))
	{
		data.direction = D3DXVECTOR3(-1, -1, -1);
		data.padding = 0;

		/*TwBar* bar = TweakBar::Get()->GetBar();
		TwAddVarRW(bar, "Directional", TW_TYPE_DIR3F, &data.direction, "group='sun'");*/
	}

	struct Data
	{
		D3DXVECTOR3 direction;
		float padding;
	};
private:
	Data data;
};
