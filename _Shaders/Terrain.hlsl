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

cbuffer PS_Terrain : register(b1)
{
    float4 _diffuse;
	float4 _ambient;
};

cbuffer PS_Brush : register(b2)
{
	float3 _pickPosition;
	float _brushSize;
	float _brushShape;
	float3 _brushPadding;
};

cbuffer PS_Grid : register(b3)
{
	float _thickness; // 선 두께
	float _gridSpace; // 그리드 간격
	float2 gridPadding;
};


struct VertexInput
{
	float3 position : POSITION0;
	float4 color : COLOR0;
    float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
	float2 uv2 : TEXCOORD1;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float3 wPosition : WPOSITION0;
	float4 color : COLOR0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
	float2 uv2 : TEXCOORD1;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;

    output.position = mul(float4(input.position, 1.0f), _world);
	output.wPosition = output.position.xyz;

    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

    output.normal = normalize(mul(input.normal, (float3x3) _world));

	output.uv = input.uv;
	output.uv2 = input.uv2;

	output.color = input.color;

	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 diffuseMap = saturate(_map[0].Sample(samp, input.uv));
	float4 c1 = saturate(_map[1].Sample(samp, input.uv2));
	float4 c2 = saturate(_map[2].Sample(samp, input.uv2));
	float4 c3 = saturate(_map[3].Sample(samp, input.uv2));
	float4 c4 = saturate(_map[4].Sample(samp, input.uv2));

	float4 color = lerp(diffuseMap, c1, input.color.r);
	color = lerp(color, c2, input.color.g);
	color = lerp(color, c3, input.color.b);
	color = lerp(color, c4, input.color.a);

    float4 result = _ambient;

    float3 light = _directional * -1;
    
    float intensity = saturate(dot(input.normal, light));

    if(intensity > 0.0f)
        result += _diffuse * intensity;
    
    result = saturate(result) * color;

	float dis = distance(_pickPosition , input.wPosition);
	float2 temp = input.wPosition.xz - _pickPosition.xz + _brushSize;

	if (_brushShape > 0.9f && dis <= _brushSize)
		result *= float4(1.0f, 0.0f, 0.0f, 1.0f);
	else if(_brushShape < 0.1f && temp.x < _brushSize * 2 && temp.x > 0 && temp.y < _brushSize * 2 && temp.y > 0)
		result *= float4(0.0f, 1.0f, 0.0f, 1.0f);

	// GRID
	/* :  HLSL내장함수

	ddx(x), ddy(x) : 스크린공간의 x, y 좌표에 대한 x, y의 편미분을 리턴한다.
	fwidth(x) : abs( ddx(x) ) + abs( ddy(x) ) 를 리턴한다.

	즉 (fwidth(coord) * _thickness)는
	그리드 라인이 어느정도 떨어져있냐에 따라 값보정(편미분이용)
	*/
	float2 coord = input.wPosition.xz / _gridSpace;
	float2 grid = abs(frac(coord - 0.5f) - 0.5f) / (fwidth(coord) * _thickness);
	float gridMin = min(grid.x, grid.y);
	float lineColor = 1.0f - min(gridMin, 1.0f);

	result.rgb += float3(lineColor, lineColor, lineColor);

    return result;
}