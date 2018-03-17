cbuffer VS_Camera : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
	float3 _cameraPosition;
	float _cameraPadding;
};

cbuffer PS_Sun : register(b0)
{
    float3 _light;
    float _padding;
}

cbuffer PS_Color
{
    float4 _ambient;
    float4 _diffuse;
    float4 _specular;
    float4 _emissive;
	float4 _normal;

	float4x4 _boneScale;
	float4x4 _boneArray[100];
	uint _skinning;
	float3 _bonePadding;
}

struct VertexInput
{
	float4 position : POSITION0;
	float3 normal : NORMAL0;
	float3 tangent : TANGENT0;
	float3 binormal : BINORMAL0;
	float2 uv : TEXCOORD0;
	float4 boneIndices : BLENDINDICES0;
	float4 boneWeights : BLENDWEIGHT0;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL0;
	float3 tangent : TANGENT0;
	float3 binormal : BINORMAL0;
	float3 viewDirection : TEXCOORD1;
	float2 uv : TEXCOORD0;
};

float3 NormalSampleToWoldSpace(float3 normalMapSample, float3 inputNormal, float3 inputTangent)
{
	// [0,1] -> [-1, 1]
	float3 normalT = 2.0f * normalMapSample - 1.0f;

	// 탄젠트공간의 정규 직교 기저 구하기
	float3 N = inputNormal;
	float3 T = normalize(inputTangent - dot(inputTangent, N)*N);
	float3 B = cross(N, T);

	float3x3 TBN = float3x3(T, B, N);

	float3 outputNormal = mul(normalT, TBN);

	return outputNormal;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;

	if (_skinning == 0)
	{
		//output.position = mul(input.position, _boneScale);
		output.position = mul(input.position, _world);
		output.normal = mul(input.normal, (float3x3) _world);
		output.normal = normalize(output.normal);
	}
	else
	{
		float4x4 skinTransform = 0;
		skinTransform += _boneArray[input.boneIndices.x] * input.boneWeights.x;
		skinTransform += _boneArray[input.boneIndices.y] * input.boneWeights.y;
		skinTransform += _boneArray[input.boneIndices.z] * input.boneWeights.z;
		skinTransform += _boneArray[input.boneIndices.w] * input.boneWeights.w;

		output.position = mul(input.position, skinTransform);
		//output.position = mul(output.position, _boneScale);
		output.position = mul(output.position, _world);

		output.normal = normalize(mul(input.normal, (float3x3) skinTransform));
	}

	output.position = mul(output.position, _boneScale);

	output.viewDirection = normalize(_cameraPosition - output.position.xyz);

	output.position = mul(output.position, _view);
	output.position = mul(output.position, _projection);

	output.tangent = normalize(mul(input.tangent, (float3x3) _world));
	output.binormal = normalize(mul(input.binormal, (float3x3) _world));

	output.normal = normalize(mul(output.normal, (float3x3) _world));

	output.uv = input.uv;

	return output;
}

SamplerState _samp : register(s0);
Texture2D _map : register(t0);

float4 PS(PixelInput input) : SV_TARGET
{
	//float4 diffuseColor = _map[0].Sample(_samp, input.uv);
	//float3 normalMap = _map[1].Sample(samp, input.uv).rgb;

	//float3 bumpedNormal = NormalSampleToWoldSpace(normalMap, input.normal, input.tangent);

	//float3 lightDir = _lightDir * -1;
	//float lightIntensity = saturate(dot(bumpedNormal, lightDir));
	//float4 color = diffuseColor * lightIntensity;

	//if (lightIntensity > 0.0f)
	//{
	//	float4 specularMap = _map[2].Sample(samp, input.uv);

	//	float3 reflection = normalize(2 * lightIntensity * bumpedNormal - lightDir);
	//	float4 specular = pow(saturate(dot(reflection, input.viewDirection)), 2.0f);
	//	specular = specular * specularMap;

	//	color = saturate(color + specular);
	//}

	//return color;

	float4 color = _map.Sample(_samp, input.uv);
	
	return color;
}