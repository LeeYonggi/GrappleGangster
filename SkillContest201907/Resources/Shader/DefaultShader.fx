struct VS_INPUT
{
	float4 mPos : POSITION;
	float2 mUV : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPos : POSITION;
	float2 mUV : TEXCOORD0;
};

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD2;
};

texture gDiffuseTex;
sampler2D gDiffuseSamler = sampler_state
{
	Texture = (gDiffuseTex);
};

float4x4 gWorldMat;
float4x4 gViewMat;


VS_OUTPUT vs_outline(VS_INPUT input)
{
	VS_OUTPUT output;

	float4 worldPos = mul(input.mPos, gWorldMat);

	output.mPos = mul(worldPos, gWorldMat);
	output.mPos = mul(output.Pos, gViewMat);

	output.mUV = input.mUV;

	return output;
}

float4 ps_main(PS_INPUT input) : COLOR
{
	float4 albedo = tex2D(gDiffuseSampler, input.mUV);
	
	albedo.a = 1;

	return float4(albedo);
}