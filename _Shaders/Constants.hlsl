cbuffer VS_ViewProjection : register(b0)
{
	matrix _view;
    matrix _projection;
}

cbuffer VS_World : register(b1)
{
	matrix _world;
}

cbuffer PS_Sun : register(b0)
{
    float3 _direction;
    float _sunPadding;
}