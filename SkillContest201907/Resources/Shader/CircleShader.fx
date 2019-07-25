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
};

texture gDiffuseTex;
sampler2D gDiffuseSampler = sampler_state
{
	Texture = (gDiffuseTex);
};

float4x4 gWorldMat;
float4x4 gViewMat;
float4x4 gProjMat;
float4 gColor;
float gDistance;

VS_OUTPUT vs_main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.mPos = mul(input.mPos, gWorldMat);
	output.mPos = mul(output.mPos, gViewMat);
	output.mPos = mul(output.mPos, gProjMat);

	output.mUV = input.mUV;

	return output;
}

float4 ps_main(PS_INPUT input) : COLOR
{
	float4 albedo = tex2D(gDiffuseSampler, input.mUV);

	if(distance(0.5, input.mUV) < gDistance)
	{
		albedo.a = 0.5;
		albedo.b = 0.5;
		albedo.r = 0.5;
	}

	return albedo;
}

technique Color
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
		AlphaBlendEnable = true;
		BlendOp = 1;
		DestBlend = 6;
		SrcBlend = 5;
	}
}