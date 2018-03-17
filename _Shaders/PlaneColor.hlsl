#include "Constants.hlsl"

cbuffer PS_Color : register(b1)
{
	float4 _color;
}

struct VertexInput
{
    float4 position : POSITION0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return _color;
}