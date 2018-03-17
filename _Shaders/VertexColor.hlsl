cbuffer VS_View : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
}

cbuffer PS_Sun : register(b0)
{
    float3 _direction;
    float _sunPadding;
}

struct VertexInput
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

    output.color = input.color;

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return input.color;
}