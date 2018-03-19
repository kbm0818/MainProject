#include "Constants.hlsl"

Texture2D _map[6] : register(t0);
SamplerState _samp;

struct VertexIn
{
	float3 PosL    : POSITION0;
};

struct VertexOut
{
	float3 PosL    : POSITION;
	float2 uv : TEXCOORD0;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.PosL = vin.PosL;
	vout.uv = float2(vout.PosL.x / 256.0f / 8.0f, vout.PosL.z / 256.0f / 8.0f);

	return vout;
}

struct PatchTess
{
	float EdgeTess[4]   : SV_TessFactor;
	float InsideTess[2] : SV_InsideTessFactor;
};

cbuffer HS_World : register(b1)
{
	matrix _worldHS;
}

cbuffer HS_CameraPosition : register(b2)
{
	float3 _cameraPositionHS;
	float _cameraPosition_Padding;
}

PatchTess ConstantHS(InputPatch<VertexOut, 4> patch, uint patchID : SV_PrimitiveID)
{
	PatchTess pt;

	const float d0 = 50.0f;
	const float d1 = 300.0f;

	pt.EdgeTess[0] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[0].PosL + patch[2].PosL), 1.0f), _worldHS).xyz, _cameraPositionHS)) / (d1 - d0)), 5);
	pt.EdgeTess[1] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[0].PosL + patch[1].PosL), 1.0f), _worldHS).xyz, _cameraPositionHS)) / (d1 - d0)), 5);
	pt.EdgeTess[2] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[1].PosL + patch[3].PosL), 1.0f), _worldHS).xyz, _cameraPositionHS)) / (d1 - d0)), 5);
	pt.EdgeTess[3] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[2].PosL + patch[3].PosL), 1.0f), _worldHS).xyz, _cameraPositionHS)) / (d1 - d0)), 5);

	float tess = 0.25f * (pt.EdgeTess[0] + pt.EdgeTess[1] + pt.EdgeTess[2] + pt.EdgeTess[3]);

	pt.InsideTess[0] = tess;
	pt.InsideTess[1] = tess;

	return pt;
}

struct HullOut
{
	float3 PosL : POSITION;
	float2 uv : TEXCOORD0;
};

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("ConstantHS")]
[maxtessfactor(64.0f)]
HullOut HS(InputPatch<VertexOut, 4> p,
	uint i : SV_OutputControlPointID,
	uint patchId : SV_PrimitiveID)
{
	HullOut hout;

	hout.PosL = p[i].PosL;
	hout.uv = p[i].uv;

	return hout;
}

struct DomainOut
{
	float4 PosH : SV_POSITION;
	float2 uv : TEXCOORD0;
};

cbuffer DS_ViewProjection : register(b0)
{
	matrix _viewDS;
	matrix _projectionDS;
}

cbuffer DS_World : register(b1)
{
	matrix _worldDS;
}

// The domain shader is called for every vertex created by the tessellator.  
// It is like the vertex shader after tessellation.
[domain("quad")]
DomainOut DS(PatchTess patchTess,
	float2 uv : SV_DomainLocation,
	const OutputPatch<HullOut, 4> quad)
{
	DomainOut dout;

	// Bilinear interpolation.
	float3 v1 = lerp(quad[0].PosL, quad[1].PosL, uv.x);
	float3 v2 = lerp(quad[2].PosL, quad[3].PosL, uv.x);
	float3 p = lerp(v1, v2, uv.y);

	float2 t1 = lerp(quad[0].uv, quad[1].uv, uv.x);
	float2 t2 = lerp(quad[2].uv, quad[3].uv, uv.x);
	float2 t = lerp(t1, t2, uv.y);

	p.y = _map[0].SampleLevel(_samp, t, 0).r * 100.0f;

	dout.uv = t;

	dout.PosH = mul(float4(p, 1.0f), _worldDS);
	dout.PosH = mul(dout.PosH, _viewDS);
	dout.PosH = mul(dout.PosH, _projectionDS);

	return dout;
}

float4 PS(DomainOut pin) : SV_Target
{
	//return _map[0].SampleLevel(_samp, pin.uv, 0);
	//return float4(_cameraPosition,1.0f);
	return float4(1.0f,0.0f,0.0f,1.0f);
}