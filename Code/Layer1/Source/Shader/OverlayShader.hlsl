#include "OverlayShader.sl"
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
    SVertexShaderOutput output = (SVertexShaderOutput) 0;
#define iPosition input.mPosition
#define iMainUV input.mMainUV
#define iDiffuse input.mDiffuse
#define oPosition output.mPosition
#define oMainUV output.mMainUV
#define oDiffuse output.mDiffuse
#include "OverlayVertexShaderCode.sl"
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
#if USE_DIFFUSE_TEXTURE||USE_FONT_TEXTURE
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);
#endif
#define iDiffuse input.mDiffuse
#define oColour output.mColour
#include "OverlayPixelShaderCode.sl"
    return output;
}