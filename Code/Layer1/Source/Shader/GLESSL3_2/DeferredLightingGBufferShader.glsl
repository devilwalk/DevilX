#include "Function.glsl"
#ifndef OUTPUT_WORLD_TANGENT
#define OUTPUT_WORLD_TANGENT 0
#endif
#ifndef OUTPUT_MAIN_UV
#define OUTPUT_MAIN_UV 0
#endif
struct SVertexShaderInput
{
	float3 mPosition : SV_Position;
	float3 mNormal : NORMAL;
#if OUTPUT_WORLD_TANGENT
	float3 mTangent : TANGENT;
#endif
#if OUTPUT_MAIN_UV
	float2 mMainUV : TEXCOORD0;
#endif
};
struct SVertexShaderOutput
{
	float4 mPosition : SV_Position;
	float3 mWorldNormal : WORLD_NORMAL;
#if OUTPUT_WORLD_TANGENT
	float3 mWorldTangent : WORLD_TANGENT;
#endif
#if OUTPUT_MAIN_UV
	float2 mMainUV : TEXCOORD0;
#endif
};
SVertexShaderOutput vsMain(SVertexShaderInput input)
{
	SVertexShaderOutput output;
	output.mPosition = mul(gViewProjectionMatrix, mul(gWorldMatrix, float4(input.mPosition, 1.0)));
	output.mWorldNormal = mul((float3x3)gWorldMatrix, input.mNormal);
#if OUTPUT_WORLD_TANGENT
	output.mWorldTangent = mul((float3x3)gWorldMatrix, input.mTangent);
#endif
#if OUTPUT_MAIN_UV
	output.mMainUV = input.mMainUV;
#endif
	return output;
}
#ifndef USE_DIFFUSE_TEXTURE
#define USE_DIFFUSE_TEXTURE 0
#endif
#ifndef USE_NORMAL_TEXTURE
#define USE_NORMAL_TEXTURE 0
#endif
#ifndef USE_ALPHA_TEST
#define USE_ALPHA_TEST 0
#endif
SamplerState gDiffuseSamplerState;
SamplerState gNormalSamplerState;
Texture2D<float4> gDiffuseTexture;
Texture2D<float4> gNormalTexture;
struct SPixelShaderOutput
{
	float4 mNormal : SV_Target0;
	float4 mDepth : SV_Target1;
};
SPixelShaderOutput psMain(SVertexShaderOutput input)
{
	SPixelShaderOutput output;
	float alpha = gAlpha;
	float3 world_normal = normalize(input.mWorldNormal);
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);
	float diffuse_texture_alpha = diffuse_texture_colour.a;
	alpha *= diffuse_texture_alpha;
#endif
#if USE_ALPHA_TEST
	clip(alpha - gAlphaTestValue);
#endif
#if USE_NORMAL_TEXTURE
	float4 normal_texture_sampler = gNormalTexture.Sample(gNormalSamplerState, input.mMainUV);
	float3 normal_texture_normal = normal_texture_sampler.xyz * 2.0 - 1.0;
	float3 world_tangent = normalize(input.mWorldTangent);
	float3 world_binormal = cross(world_normal, world_tangent);
	float3x3 tbn = float3x3(world_tangent, world_binormal, world_normal);
	world_normal = mul(tbn, normal_texture_normal);
#endif
	output.mNormal.xyz = encodeNormal(world_normal);
	output.mNormal.w = 0;
	output.mDepth = input.mPosition.w * gInverseFarDistance;
	return output;
}