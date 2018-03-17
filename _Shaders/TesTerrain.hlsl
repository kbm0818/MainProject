Texture2D _map[6] : register(t0);
SamplerState _samp;

cbuffer DS_View : register(b0)
{
	matrix _world;
	matrix _view;
	matrix _projection;

	float3 _cameraPosition;
	float cameraPadding;
};

cbuffer HS_View : register(b0)
{
	matrix _hworld;
	matrix _hview;
	matrix _hprojection;

	float3 _hcameraPosition;
	float hcameraPadding;
};

cbuffer PS_Sun : register(b0)
{
	float3 _directional;
	float _sunPadding;
}

/////////////////////////////////////////////////////////////////////////

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

PatchTess ConstantHS(InputPatch<VertexOut, 4> patch, uint patchID : SV_PrimitiveID)
{
	PatchTess pt;

	const float d0 = 50.0f;
	const float d1 = 300.0f;

	pt.EdgeTess[0] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[0].PosL + patch[2].PosL), 1.0f), _hworld).xyz, _hcameraPosition)) / (d1 - d0)), 5);
	pt.EdgeTess[1] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[0].PosL + patch[1].PosL), 1.0f), _hworld).xyz, _hcameraPosition)) / (d1 - d0)), 5);
	pt.EdgeTess[2] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[1].PosL + patch[3].PosL), 1.0f), _hworld).xyz, _hcameraPosition)) / (d1 - d0)), 5);
	pt.EdgeTess[3] = 64.0f * pow(saturate((d1 - distance(mul(float4(0.5f * (patch[2].PosL + patch[3].PosL), 1.0f), _hworld).xyz, _hcameraPosition)) / (d1 - d0)), 5);

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

	dout.PosH = mul(float4(p, 1.0f), _world);
	dout.PosH = mul(dout.PosH, _view);
	dout.PosH = mul(dout.PosH, _projection);

	return dout;
}

float4 PS(DomainOut pin) : SV_Target
{
	return _map[0].SampleLevel(_samp, pin.uv, 0);
	//return float4(_cameraPosition,1.0f);
}