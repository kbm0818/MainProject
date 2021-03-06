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

cbuffer PS_Sky : register(b1)
{
    float4 _center;
    float4 _apex;
}

struct VertexInput
{
    float4 position : POSITION0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 wPosition : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

    output.wPosition = input.position;

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
   /* float height = saturate(input.wPosition.y);

    return lerp(_center, _apex + float4(0.5f, 0.0f, 0.0f, 1.0f), height);*/
	return float4(1,0,0,1);
}