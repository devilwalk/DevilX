#include "Function.hlsl"
#ifndef USE_DIFFUSE_TEXTURE
#define USE_DIFFUSE_TEXTURE 0
#endif
#ifndef USE_VERTEX_DIFFUSE
#define USE_VERTEX_DIFFUSE 0
#endif
struct SVertexShaderInput
{
    float3 mPosition : SV_Position;
#if USE_DIFFUSE_TEXTURE
	float2 mMainUV : TEXCOORD0;
#endif
#if USE_VERTEX_DIFFUSE
    float4 mDiffuse : DIFFUSE;
#endif
};
struct SVertexShaderOutput
{
    float3 mWorldPosition : WORLD_POSITION;
#if USE_DIFFUSE_TEXTURE
	float2 mMainUV : TEXCOORD0;
#endif
#if USE_VERTEX_DIFFUSE
    float4 mDiffuse : DIFFUSE;
#endif
};
SVertexShaderOutput vsMain(SVertexShaderInput input)
{
    SVertexShaderOutput output = (SVertexShaderOutput) 0;
    output.mWorldPosition = mul(gWorldMatrix, float4(input.mPosition, 1.0)).xyz;
#if USE_DIFFUSE_TEXTURE
	output.mMainUV = input.mMainUV;
#endif
#if USE_VERTEX_DIFFUSE
	output.mDiffuse = input.mDiffuse;
#endif
    return output;
}
struct SGeometryShaderOutput
{
    float4 mPosition : SV_Position;
    uint mViewportIndex : SV_ViewportArrayIndex;
#if USE_DIFFUSE_TEXTURE
	float2 mMainUV : TEXCOORD0;
#endif
#if USE_VERTEX_DIFFUSE
    float4 mDiffuse : DIFFUSE;
#endif
};
[maxvertexcount(12)]
void gsMain(triangle SVertexShaderOutput input[3], inout TriangleStream<SGeometryShaderOutput> outputs)
{
    for (int i0 = 0; i0 < 3; ++i0)
    {
        SGeometryShaderOutput output;
        output.mPosition = mul(gShadowMap0ViewProjectionMatrix, float4(input[i0].mWorldPosition, 1.0));
        output.mPosition.xy /= output.mPosition.w;
        output.mPosition.z = output.mPosition.w * gShadowMap0InverseFarDistance;
        output.mPosition.w = 1.0;
        output.mViewportIndex = 0;
#if USE_DIFFUSE_TEXTURE
        output.mMainUV = input[i0].mMainUV;
#endif
#if USE_VERTEX_DIFFUSE
	    output.mDiffuse = input[i0].mDiffuse;
#endif
        outputs.Append(output);
    }
    outputs.RestartStrip();

    for (int i1 = 0; i1 < 3; ++i1)
    {
        SGeometryShaderOutput output;
        output.mPosition = mul(gShadowMap1ViewProjectionMatrix, float4(input[i1].mWorldPosition, 1.0));
        output.mPosition.xy /= output.mPosition.w;
        output.mPosition.z = output.mPosition.w * gShadowMap1InverseFarDistance;
        output.mPosition.w = 1.0;
        output.mViewportIndex = 1;
#if USE_DIFFUSE_TEXTURE
        output.mMainUV = input[i1].mMainUV;
#endif
#if USE_VERTEX_DIFFUSE
	    output.mDiffuse = input[i1].mDiffuse;
#endif
        outputs.Append(output);
    }
    outputs.RestartStrip();

    for (int i2 = 0; i2 < 3; ++i2)
    {
        SGeometryShaderOutput output;
        output.mPosition = mul(gShadowMap0ViewProjectionMatrix, float4(input[i2].mWorldPosition, 1.0));
        output.mPosition.xy /= output.mPosition.w;
        output.mPosition.z = output.mPosition.w * gShadowMap0InverseFarDistance;
        output.mPosition.w = 1.0;
        output.mViewportIndex = 2;
#if USE_DIFFUSE_TEXTURE
        output.mMainUV = input[i2].mMainUV;
#endif
#if USE_VERTEX_DIFFUSE
	    output.mDiffuse = input[i2].mDiffuse;
#endif
        outputs.Append(output);
    }
    outputs.RestartStrip();

    for (int i3 = 0; i3 < 3; ++i3)
    {
        SGeometryShaderOutput output;
        output.mPosition = mul(gShadowMap0ViewProjectionMatrix, float4(input[i3].mWorldPosition, 1.0));
        output.mPosition.xy /= output.mPosition.w;
        output.mPosition.z = output.mPosition.w * gShadowMap0InverseFarDistance;
        output.mPosition.w = 1.0;
        output.mViewportIndex = 3;
#if USE_DIFFUSE_TEXTURE
        output.mMainUV = input[i3].mMainUV;
#endif
#if USE_VERTEX_DIFFUSE
	    output.mDiffuse = input[i3].mDiffuse;
#endif
        outputs.Append(output);
    }
    outputs.RestartStrip();
}
SamplerState gDiffuseSamplerState;
Texture2D<float4> gDiffuseTexture;
struct SPixelShaderOutput
{
    float4 mColour : SV_Target;
};
SPixelShaderOutput psMain(SGeometryShaderOutput input)
{
    SPixelShaderOutput output = (SPixelShaderOutput) 0;
#if USE_DIFFUSE_TEXTURE || USE_VERTEX_DIFFUSE
    float alpha = 1.0;
#if USE_DIFFUSE_TEXTURE
	float diffuse_texture_alpha = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV).a;
	alpha *= diffuse_texture_alpha;
#endif
#if USE_VERTEX_DIFFUSE
	alpha *= input.mDiffuse.a;
#endif
	clip(alpha - gAlphaTestValue);
#endif
    return output;
}