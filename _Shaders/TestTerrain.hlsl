Texture2D _map[5] : register(t0);
SamplerState samp;

cbuffer VS_View : register(b0)
{
	matrix _world;
	matrix _view;
	matrix _projection;
};

cbuffer PS_Sun : register(b0)
{
	float3 _directional;
	float _sunPadding;
}

struct VertexInput
{
	float3 position : POSITION0;
};

struct PixelInput
{
	float4 position : SV_POSITION;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;

    output.position = mul(float4(input.position, 1.0f), _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
   return float4(1.0f,0.0f,0.0f,1.0f);
}