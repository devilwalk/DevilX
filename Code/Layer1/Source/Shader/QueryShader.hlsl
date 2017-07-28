#include "QueryShader.sl"
struct SVertexShaderInput
{
    float3 mPosition : SV_Position;
#if OUTPUT_MAIN_UV
    float2 mMainUV : TEXCOORD0;
#endif
    float4 mQuery : QUERY;
};
struct SVertexShaderOutput
{
    float4 mPosition : SV_Position;
#if OUTPUT_MAIN_UV
    float2 mMainUV : TEXCOORD0;
 #endif
    nointerpolation float4 mQuery : QUERY;
};
SVertexShaderOutput vsMain(SVertexShaderInput input)
{
    SVertexShaderOutput output = (SVertexShaderOutput) 0;
#define iPosition input.mPosition
#define iMainUV input.mMainUV
#define iQuery input.mQuery
#define oPosition output.mPosition
#define oMainUV output.mMainUV
#define oQuery output.mQuery
#include "QueryVertexShaderCode.sl"
    return output;
}
SamplerState gDiffuseSamplerState;
Texture2D<float4> gDiffuseTexture;
struct SPixelShaderOutput
{
    float4 mColour : SV_Target;
};
SPixelShaderOutput psMain(SVertexShaderOutput input)
{
    SPixelShaderOutput output = (SPixelShaderOutput) 0;
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);
#endif
#define iQuery input.mQuery
#define oColour output.mColour
#include "QueryPixelShaderCode.sl"
    return output;
}