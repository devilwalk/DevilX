#include "ForwardShader.sl"
struct SVertexShaderInput
{
	float3 mPosition : SV_Position;
#if OUTPUT_WORLD_NORMAL
	float3 mNormal : NORMAL;
#endif
#if OUTPUT_WORLD_TANGENT
	float3 mTangent : TANGENT;
#endif
#if OUTPUT_MAIN_UV
	float2 mMainUV : TEXCOORD0;
#endif
#if OUTPUT_DIFFUSE
    float4 mDiffuse : DIFFUSE;
#endif
};
struct SVertexShaderOutput
{
	float4 mPosition : SV_Position;
#if OUTPUT_WORLD_POSITION
	float3 mWorldPosition : WORLD_POSITION;
#endif
#if OUTPUT_WORLD_NORMAL
	float3 mWorldNormal : WORLD_NORMAL;
#endif
#if OUTPUT_WORLD_TANGENT
	float3 mWorldTangent : WORLD_TANGENT;
#endif
#if OUTPUT_MAIN_UV
	float2 mMainUV : TEXCOORD0;
#endif
#if OUTPUT_DIFFUSE
    float4 mDiffuse : DIFFUSE;
#endif
};
SVertexShaderOutput vsMain(SVertexShaderInput input)
{
    SVertexShaderOutput output = (SVertexShaderOutput) 0;
#define iPosition input.mPosition
#define iNormal input.mNormal
#define iTangent input.mTangent
#define iMainUV input.mMainUV
#define iDiffuse input.mDiffuse
#define oPosition output.mPosition
#define oWorldPosition output.mWorldPosition
#define oWorldNormal output.mWorldNormal
#define oWorldTangent output.mWorldTangent
#define oMainUV output.mMainUV
#define oDiffuse output.mDiffuse
#include "ForwardVertexShaderCode.sl"
    return output;
}
SamplerState gDiffuseSamplerState;
SamplerState gNormalSamplerState;
Texture2D<float4> gDiffuseTexture;
Texture2D<float4> gNormalTexture;
struct SPixelShaderOutput
{
	float4 mColour : SV_Target;
};
SPixelShaderOutput psMain(SVertexShaderOutput input)
{
    SPixelShaderOutput output = (SPixelShaderOutput)0;
#define iWorldPosition input.mWorldPosition
#define iWorldNormal input.mWorldNormal
#define iWorldTangent input.mWorldTangent
#define iMainUV input.mMainUV
#define iDiffuse input.mDiffuse
#define oColour output.mColour
#include "ForwardPixelShaderCode.sl"
	return output;
}