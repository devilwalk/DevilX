#include "Function.hlsl"
struct SVertexShaderInput
{
    float3 mPosition : SV_Position;
	float2 mMainUV : TEXCOORD0;
    float4 mDiffuse : DIFFUSE;
};
struct SVertexShaderOutput
{
    float4 mPosition : SV_Position;
	float2 mMainUV : TEXCOORD0;
    float4 mDiffuse : DIFFUSE;
};
SVertexShaderOutput vsMain(SVertexShaderInput input)
{
    SVertexShaderOutput output;
    output.mPosition = float4(input.mPosition, 1.0);
	output.mMainUV = input.mMainUV;
	output.mDiffuse = input.mDiffuse;
    return output;
}
#ifndef USE_DIFFUSE_TEXTURE
#define USE_DIFFUSE_TEXTURE 0
#endif
SamplerState gDiffuseSamplerState;
Texture2D<float4> gDiffuseTexture;
struct SPixelShaderOutput
{
    float4 mColour : SV_Target;
};
SPixelShaderOutput psMain(SVertexShaderOutput input)
{
    SPixelShaderOutput output = (SPixelShaderOutput) 0;
    float3 colour_emissive = input.mDiffuse.rgb;
    float alpha = input.mDiffuse.a;
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;
	float diffuse_texture_alpha = diffuse_texture_sampler.a;
	alpha *= diffuse_texture_alpha;
	colour_emissive *= diffuse_texture_colour;
#endif
    output.mColour.rgb = colour_emissive;
    output.mColour.a = alpha;
    return output;
}