#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSHLSL5;
NSDevilX::NSRenderSystem::NSHLSL5::CDefinitionShader::CDefinitionShader()
{
CascadedShadowMap="#include \"Function.hlsl\"\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_VERTEX_DIFFUSE\r\n\
#define USE_VERTEX_DIFFUSE 0\r\n\
#endif\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
    float3 mPosition : SV_Position;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
#endif\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
    float3 mWorldPosition : WORLD_POSITION;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
#endif\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
    SVertexShaderOutput output = (SVertexShaderOutput) 0;\r\n\
    output.mWorldPosition = mul(gWorldMatrix, float4(input.mPosition, 1.0)).xyz;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	output.mMainUV = input.mMainUV;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
	output.mDiffuse = input.mDiffuse;\r\n\
#endif\r\n\
    return output;\r\n\
}\r\n\
struct SGeometryShaderOutput\r\n\
{\r\n\
    float4 mPosition : SV_Position;\r\n\
    uint mViewportIndex : SV_ViewportArrayIndex;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
#endif\r\n\
};\r\n\
[maxvertexcount(12)]\r\n\
void gsMain(triangle SVertexShaderOutput input[3], inout TriangleStream<SGeometryShaderOutput> outputs)\r\n\
{\r\n\
    for (int i0 = 0; i0 < 3; ++i0)\r\n\
    {\r\n\
        SGeometryShaderOutput output;\r\n\
        output.mPosition = mul(gShadowMap0ViewProjectionMatrix, float4(input[i0].mWorldPosition, 1.0));\r\n\
        output.mPosition.xy /= output.mPosition.w;\r\n\
        output.mPosition.z = output.mPosition.w * gShadowMap0InverseFarDistance;\r\n\
        output.mPosition.w = 1.0;\r\n\
        output.mViewportIndex = 0;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
        output.mMainUV = input[i0].mMainUV;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
	    output.mDiffuse = input[i0].mDiffuse;\r\n\
#endif\r\n\
        outputs.Append(output);\r\n\
    }\r\n\
    outputs.RestartStrip();\r\n\
\r\n\
    for (int i1 = 0; i1 < 3; ++i1)\r\n\
    {\r\n\
        SGeometryShaderOutput output;\r\n\
        output.mPosition = mul(gShadowMap1ViewProjectionMatrix, float4(input[i1].mWorldPosition, 1.0));\r\n\
        output.mPosition.xy /= output.mPosition.w;\r\n\
        output.mPosition.z = output.mPosition.w * gShadowMap1InverseFarDistance;\r\n\
        output.mPosition.w = 1.0;\r\n\
        output.mViewportIndex = 1;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
        output.mMainUV = input[i1].mMainUV;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
	    output.mDiffuse = input[i1].mDiffuse;\r\n\
#endif\r\n\
        outputs.Append(output);\r\n\
    }\r\n\
    outputs.RestartStrip();\r\n\
\r\n\
    for (int i2 = 0; i2 < 3; ++i2)\r\n\
    {\r\n\
        SGeometryShaderOutput output;\r\n\
        output.mPosition = mul(gShadowMap0ViewProjectionMatrix, float4(input[i2].mWorldPosition, 1.0));\r\n\
        output.mPosition.xy /= output.mPosition.w;\r\n\
        output.mPosition.z = output.mPosition.w * gShadowMap0InverseFarDistance;\r\n\
        output.mPosition.w = 1.0;\r\n\
        output.mViewportIndex = 2;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
        output.mMainUV = input[i2].mMainUV;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
	    output.mDiffuse = input[i2].mDiffuse;\r\n\
#endif\r\n\
        outputs.Append(output);\r\n\
    }\r\n\
    outputs.RestartStrip();\r\n\
\r\n\
    for (int i3 = 0; i3 < 3; ++i3)\r\n\
    {\r\n\
        SGeometryShaderOutput output;\r\n\
        output.mPosition = mul(gShadowMap0ViewProjectionMatrix, float4(input[i3].mWorldPosition, 1.0));\r\n\
        output.mPosition.xy /= output.mPosition.w;\r\n\
        output.mPosition.z = output.mPosition.w * gShadowMap0InverseFarDistance;\r\n\
        output.mPosition.w = 1.0;\r\n\
        output.mViewportIndex = 3;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
        output.mMainUV = input[i3].mMainUV;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
	    output.mDiffuse = input[i3].mDiffuse;\r\n\
#endif\r\n\
        outputs.Append(output);\r\n\
    }\r\n\
    outputs.RestartStrip();\r\n\
}\r\n\
SamplerState gDiffuseSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
    float4 mColour : SV_Target;\r\n\
};\r\n\
SPixelShaderOutput psMain(SGeometryShaderOutput input)\r\n\
{\r\n\
    SPixelShaderOutput output = (SPixelShaderOutput) 0;\r\n\
#if USE_DIFFUSE_TEXTURE || USE_VERTEX_DIFFUSE\r\n\
    float alpha = 1.0;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float diffuse_texture_alpha = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV).a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
#endif\r\n\
#if USE_VERTEX_DIFFUSE\r\n\
	alpha *= input.mDiffuse.a;\r\n\
#endif\r\n\
	clip(alpha - gAlphaTestValue);\r\n\
#endif\r\n\
    return output;\r\n\
}";
ClearViewport="#include \"Function.hlsl\"\r\n\
cbuffer cbClearViewport\r\n\
{\r\n\
    float4 gClearColour0 : packoffset(c0);\r\n\
    float4 gClearColour1 : packoffset(c1);\r\n\
    float4 gClearColour2 : packoffset(c2);\r\n\
    float4 gClearColour3 : packoffset(c3);\r\n\
    float4 gClearColour4 : packoffset(c4);\r\n\
    float4 gClearColour5 : packoffset(c5);\r\n\
    float4 gClearColour6 : packoffset(c6);\r\n\
    float4 gClearColour7 : packoffset(c7);\r\n\
    float gClearDepth : packoffset(c8);\r\n\
};\r\n\
void vsMain\r\n\
(uint vertexID : SV_VertexID\r\n\
, out float4 outPosition : SV_Position\r\n\
)\r\n\
{\r\n\
    float depth = gClearDepth;\r\n\
    outPosition = float4(getQuadPosition(vertexID), depth, 1.0);\r\n\
}\r\n\
void psMain\r\n\
(float4 position : SV_Position\r\n\
, out float4 outColour0 : SV_Target0\r\n\
, out float4 outColour1 : SV_Target1\r\n\
, out float4 outColour2 : SV_Target2\r\n\
, out float4 outColour3 : SV_Target3\r\n\
, out float4 outColour4 : SV_Target4\r\n\
, out float4 outColour5 : SV_Target5\r\n\
, out float4 outColour6 : SV_Target6\r\n\
, out float4 outColour7 : SV_Target7\r\n\
)\r\n\
{\r\n\
    outColour0 = gClearColour0;\r\n\
    outColour1 = gClearColour1;\r\n\
    outColour2 = gClearColour2;\r\n\
    outColour3 = gClearColour3;\r\n\
    outColour4 = gClearColour4;\r\n\
    outColour5 = gClearColour5;\r\n\
    outColour6 = gClearColour6;\r\n\
    outColour7 = gClearColour7;\r\n\
}";
ConstantBuffer="cbuffer cbSystem\r\n\
{\r\n\
    float gFrameTimeInSeconds : packoffset(c0);\r\n\
    float gInverseFrameTimeInSeconds : packoffset(c0.y);\r\n\
};\r\n\
cbuffer cbRenderTarget\r\n\
{\r\n\
    float2 gRenderTargetSizeInPixel : packoffset(c0);\r\n\
    float2 gInverseRenderTargetSizeInPixel : packoffset(c0.z);\r\n\
};\r\n\
cbuffer cbViewport\r\n\
{\r\n\
    float2 gViewportSizeInPixel : packoffset(c0);\r\n\
    float2 gInverseViewportSizeInPixel : packoffset(c0.z);\r\n\
};\r\n\
cbuffer cbCamera\r\n\
{\r\n\
    float4x4 gViewMatrix : packoffset(c0);\r\n\
    float4x4 gInverseViewMatrix : packoffset(c4);\r\n\
    float4x4 gProjectionMatrix : packoffset(c8);\r\n\
    float4x4 gInverseProjectionMatrix : packoffset(c12);\r\n\
    float4x4 gViewProjectionMatrix : packoffset(c16);\r\n\
    float4x4 gInverseViewProjectionMatrix : packoffset(c20);\r\n\
    float gFarDistance : packoffset(c24);\r\n\
    float gInverseFarDistance : packoffset(c24.y);\r\n\
};\r\n\
cbuffer cbShadowMap0\r\n\
{\r\n\
    float4x4 gShadowMap0ViewProjectionMatrix : packoffset(c0);\r\n\
    float gShadowMap0FarDistance : packoffset(c4);\r\n\
    float gShadowMap0InverseFarDistance : packoffset(c5);\r\n\
};\r\n\
cbuffer cbShadowMap1\r\n\
{\r\n\
    float4x4 gShadowMap1ViewProjectionMatrix : packoffset(c0);\r\n\
    float gShadowMap1FarDistance : packoffset(c4);\r\n\
    float gShadowMap1InverseFarDistance : packoffset(c5);\r\n\
};\r\n\
cbuffer cbShadowMap2\r\n\
{\r\n\
    float4x4 gShadowMap2ViewProjectionMatrix : packoffset(c0);\r\n\
    float gShadowMap2FarDistance : packoffset(c4);\r\n\
    float gShadowMap2InverseFarDistance : packoffset(c5);\r\n\
};\r\n\
cbuffer cbShadowMap3\r\n\
{\r\n\
    float4x4 gShadowMap3ViewProjectionMatrix : packoffset(c0);\r\n\
    float gShadowMap3FarDistance : packoffset(c4);\r\n\
    float gShadowMap3InverseFarDistance : packoffset(c5);\r\n\
};\r\n\
cbuffer cbDirectionLight\r\n\
{\r\n\
    float3 gDirectionLightDiffuseColour : packoffset(c0);\r\n\
    float3 gDirectionLightSpecularColour : packoffset(c1);\r\n\
    float3 gDirectionLightDirection : packoffset(c2);\r\n\
};\r\n\
cbuffer cbPointLight\r\n\
{\r\n\
    float3 gPointLightDiffuseColour : packoffset(c0);\r\n\
    float3 gPointLightSpecularColour : packoffset(c1);\r\n\
    float3 gPointLightPosition : packoffset(c2);\r\n\
    float gPointLightReciprocalRange : packoffset(c0.w);\r\n\
    float gPointLightStartFallOffDistance : packoffset(c1.w);\r\n\
};\r\n\
cbuffer cbSpotLight\r\n\
{\r\n\
    float3 gSpotLightDiffuseColour : packoffset(c0);\r\n\
    float3 gSpotLightSpecularColour : packoffset(c1);\r\n\
    float3 gSpotLightDirection : packoffset(c2);\r\n\
    float3 gSpotLightPosition : packoffset(c3);\r\n\
    float gSpotLightReciprocalRange : packoffset(c0.w);\r\n\
    float gSpotLightStartFallOffDistance : packoffset(c1.w);\r\n\
    float gSpotLightCosInnerCornerHalfAngle : packoffset(c2.w);\r\n\
    float gSpotLightReciprocalDeltaCosHalfAngle : packoffset(c3.w);\r\n\
};\r\n\
cbuffer cbScene\r\n\
{\r\n\
    float3 gAmbientColour : packoffset(c0);\r\n\
};\r\n\
cbuffer cbObjectTransform\r\n\
{\r\n\
    float4x4 gWorldMatrix : packoffset(c0);\r\n\
};\r\n\
cbuffer cbObjectMaterial\r\n\
{\r\n\
    float3 gMainColour : packoffset(c0);\r\n\
    float gAlpha : packoffset(c0.w);\r\n\
    float3 gSpecularColour : packoffset(c1);\r\n\
    float gSpecularPower : packoffset(c1.w);\r\n\
    float3 gEmissiveColour : packoffset(c2);\r\n\
    float gAlphaTestValue : packoffset(c2.w);\r\n\
};";
DeferredLightingGBufferShader="#include \"Function.hlsl\"\r\n\
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
	float3 mPosition : SV_Position;\r\n\
	float3 mNormal : NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mTangent : TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
	float4 mPosition : SV_Position;\r\n\
	float3 mWorldNormal : WORLD_NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mWorldTangent : WORLD_TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
	SVertexShaderOutput output;\r\n\
	output.mPosition = mul(gViewProjectionMatrix, mul(gWorldMatrix, float4(input.mPosition, 1.0)));\r\n\
	output.mWorldNormal = mul((float3x3)gWorldMatrix, input.mNormal);\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	output.mWorldTangent = mul((float3x3)gWorldMatrix, input.mTangent);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	output.mMainUV = input.mMainUV;\r\n\
#endif\r\n\
	return output;\r\n\
}\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
SamplerState gDiffuseSamplerState;\r\n\
SamplerState gNormalSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
Texture2D<float4> gNormalTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
	float4 mNormal : SV_Target0;\r\n\
	float4 mDepth : SV_Target1;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
	SPixelShaderOutput output;\r\n\
	float alpha = gAlpha;\r\n\
	float3 world_normal = normalize(input.mWorldNormal);\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
	float diffuse_texture_alpha = diffuse_texture_colour.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	clip(alpha - gAlphaTestValue);\r\n\
#endif\r\n\
#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler = gNormalTexture.Sample(gNormalSamplerState, input.mMainUV);\r\n\
	float3 normal_texture_normal = normal_texture_sampler.xyz * 2.0 - 1.0;\r\n\
	float3 world_tangent = normalize(input.mWorldTangent);\r\n\
	float3 world_binormal = cross(world_normal, world_tangent);\r\n\
	float3x3 tbn = float3x3(world_tangent, world_binormal, world_normal);\r\n\
	world_normal = mul(tbn, normal_texture_normal);\r\n\
#endif\r\n\
	output.mNormal.xyz = encodeNormal(world_normal);\r\n\
	output.mNormal.w = 0;\r\n\
	output.mDepth = input.mPosition.w * gInverseFarDistance;\r\n\
	return output;\r\n\
}";
DeferredShadingGBufferShader="#include \"Function.hlsl\"\r\n\
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
	float3 mPosition : SV_Position;\r\n\
	float3 mNormal : NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mTangent : TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
	float4 mPosition : SV_Position;\r\n\
	float3 mWorldNormal : WORLD_NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mWorldTangent : WORLD_TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
	SVertexShaderOutput output;\r\n\
	output.mPosition = mul(gViewProjectionMatrix, mul(gWorldMatrix, float4(input.mPosition, 1.0)));\r\n\
	output.mWorldNormal = mul((float3x3)gWorldMatrix, input.mNormal);\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	output.mWorldTangent = mul((float3x3)gWorldMatrix, input.mTangent);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	output.mMainUV = input.mMainUV;\r\n\
#endif\r\n\
	return output;\r\n\
}\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
SamplerState gDiffuseSamplerState;\r\n\
SamplerState gNormalSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
Texture2D<float4> gNormalTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
	float4 mColour : SV_Target0;\r\n\
	float4 mSpecular : SV_Target1;\r\n\
	float4 mNormal : SV_Target2;\r\n\
	float4 mDepth : SV_Target3;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
	SPixelShaderOutput output;\r\n\
	float3 colour_main = gMainColour;\r\n\
	float3 colour_specular = gSpecularColour;\r\n\
	float alpha = gAlpha;\r\n\
	float3 world_normal = normalize(input.mWorldNormal);\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_colour.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_main *= diffuse_texture_colour;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	clip(alpha - gAlphaTestValue);\r\n\
#endif\r\n\
#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler = gNormalTexture.Sample(gNormalSamplerState, input.mMainUV);\r\n\
	float3 normal_texture_normal = normal_texture_sampler.xyz * 2.0 - 1.0;\r\n\
	float3 world_tangent = normalize(input.mWorldTangent);\r\n\
	float3 world_binormal = cross(world_normal, world_tangent);\r\n\
	float3x3 tbn = float3x3(world_tangent, world_binormal, world_normal);\r\n\
	world_normal = mul(tbn, normal_texture_normal);\r\n\
#endif\r\n\
	output.mColour.a = alpha;\r\n\
	output.mColour.rgb = colour_main;\r\n\
	output.mSpecular.rgb = colour_specular;\r\n\
	output.mSpecular.a = gSpecularPower;\r\n\
	output.mNormal.xyz = encodeNormal(world_normal);\r\n\
	output.mNormal.w = 0;\r\n\
	output.mDepth = input.mPosition.w * gInverseFarDistance;\r\n\
	return output;\r\n\
}";
ForwardShader="#include \"Function.hlsl\"\r\n\
#ifndef OUTPUT_WORLD_POSITION\r\n\
#define OUTPUT_WORLD_POSITION 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_NORMAL\r\n\
#define OUTPUT_WORLD_NORMAL 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
#ifndef OUTPUT_DIFFUSE\r\n\
#define OUTPU_DIFFUSE 0\r\n\
#endif\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
	float3 mPosition : SV_Position;\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	float3 mNormal : NORMAL;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mTangent : TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
#endif\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
	float4 mPosition : SV_Position;\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
	float3 mWorldPosition : WORLD_POSITION;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	float3 mWorldNormal : WORLD_NORMAL;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mWorldTangent : WORLD_TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
#endif\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
	SVertexShaderOutput output;\r\n\
    float4 world_position = mul(gWorldMatrix, float4(input.mPosition, 1.0));\r\n\
    output.mPosition = mul(gViewProjectionMatrix, world_position);\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
	output.mWorldPosition = world_position.xyz;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	output.mWorldNormal = mul((float3x3)gWorldMatrix, input.mNormal);\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	output.mWorldTangent = mul((float3x3)gWorldMatrix, input.mTangent);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	output.mMainUV = input.mMainUV;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
	output.mDiffuse = input.mDiffuse;\r\n\
#endif\r\n\
	return output;\r\n\
}\r\n\
#ifndef USE_LIGHTING\r\n\
#define USE_LIGHTING 0\r\n\
#endif\r\n\
#ifndef USE_DIRECTION_LIGHT\r\n\
#define USE_DIRECTION_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_POINT_LIGHT\r\n\
#define USE_POINT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_SPOT_LIGHT\r\n\
#define USE_SPOT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
#ifndef USE_SPECULAR\r\n\
#define USE_SPECULAR 0\r\n\
#endif\r\n\
SamplerState gDiffuseSamplerState;\r\n\
SamplerState gNormalSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
Texture2D<float4> gNormalTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
	float4 mColour : SV_Target;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
    SPixelShaderOutput output = (SPixelShaderOutput)0;\r\n\
	float3 colour_emissive = gEmissiveColour;\r\n\
	float3 colour_diffuse_factor = gMainColour;\r\n\
    float3 colour_specular_factor = gSpecularColour;\r\n\
    float alpha = gAlpha;\r\n\
#if OUTPUT_DIFFUSE\r\n\
    colour_emissive *= input.mDiffuse.rgb;\r\n\
    colour_diffuse_factor *= input.mDiffuse.rgb;\r\n\
    alpha *= input.mDiffuse.a;\r\n\
#endif\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_sampler.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_diffuse_factor *= diffuse_texture_colour;\r\n\
	colour_emissive *= diffuse_texture_colour;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	clip(alpha - gAlphaTestValue);\r\n\
#endif\r\n\
#if USE_LIGHTING\r\n\
    #if USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT\r\n\
    float3 lighting_colour=0;\r\n\
    float lighting_falloff_factor=1.0;\r\n\
	float3 world_normal=normalize(input.mWorldNormal);\r\n\
		#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler=gNormalTexture.Sample(gNormalSamplerState,input.mMainUV);\r\n\
	float3 normal_texture_normal=normal_texture_sampler.xyz * 2.0-1.0;\r\n\
	float3 world_tangent=normalize(input.mWorldTangent);\r\n\
	float3 world_binormal=cross(world_normal,world_tangent);\r\n\
	float3x3 tbn=float3x3(world_tangent,world_binormal,world_normal);\r\n\
	world_normal=mul(tbn,normal_texture_normal);\r\n\
		#endif\r\n\
		#if USE_DIRECTION_LIGHT\r\n\
	float3 vertex_to_light_direction = -gDirectionLightDirection;\r\n\
    float3 light_diffuse_colour = gDirectionLightDiffuseColour;\r\n\
    float3 light_specular_colour = gDirectionLightSpecularColour;\r\n\
	    #elif USE_POINT_LIGHT\r\n\
    float3 vertex_to_light = gPointLightPosition - input.mWorldPosition;\r\n\
    lighting_falloff_factor=calcFalloffFactor(length(vertex_to_light),gPointLightStartFallOffDistance,gPointLightReciprocalRange);\r\n\
	float3 vertex_to_light_direction = normalize(vertex_to_light);\r\n\
    float3 light_diffuse_colour = gPointLightDiffuseColour;\r\n\
    float3 light_specular_colour = gPointLightSpecularColour;\r\n\
	    #elif USE_SPOT_LIGHT\r\n\
    float3 vertex_to_light = gSpotLightPosition - input.mWorldPosition;\r\n\
    float falloff_distance_factor=calcFalloffFactor(length(vertex_to_light),gSpotLightStartFallOffDistance,gSpotLightReciprocalRange);\r\n\
	float3 vertex_to_light_direction = normalize(vertex_to_light);\r\n\
    float falloff_angle_factor=calcFalloffFactor(dot(vertex_to_light_direction,gSpotLightDirection),gSpotLightCosInnerCornerHalfAngle,gSpotLightReciprocalDeltaCosHalfAngle);\r\n\
    lighting_falloff_factor=falloff_distance_factor*falloff_angle_factor;\r\n\
    float3 light_diffuse_colour = gSpotLightDiffuseColour;\r\n\
    float3 light_specular_colour = gSpotLightSpecularColour;\r\n\
	    #endif\r\n\
	float lighting_diffuse_factor = calcDiffuseFactor(vertex_to_light_direction, world_normal);\r\n\
    float3 lighting_diffuse_colour = light_diffuse_colour * lighting_diffuse_factor;\r\n\
	lighting_colour+=lighting_diffuse_colour;\r\n\
		#if USE_SPECULAR\r\n\
	float lighting_specular_factor=calcSpecularFactor(vertex_to_light_direction,world_normal,input.mWorldPosition,getCameraPosition());\r\n\
	float3 lighting_specular_colour=lighting_diffuse_factor > 0.0?pow(lighting_specular_factor,gSpecularPower) * light_specular_colour:0.0;\r\n\
	lighting_colour+=lighting_specular_colour;\r\n\
		#endif\r\n\
    output.mColour.rgb+=lighting_colour*lighting_falloff_factor*colour_diffuse_factor;\r\n\
	#else\r\n\
	output.mColour.rgb+=gAmbientColour*colour_diffuse_factor;\r\n\
	output.mColour.rgb+=colour_emissive;\r\n\
	#endif\r\n\
#else\r\n\
	output.mColour.rgb += colour_emissive;\r\n\
#endif\r\n\
	output.mColour.a = alpha;\r\n\
	return output;\r\n\
}";
Function="#include \"ConstantBuffer.hlsl\"\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraPosition()\r\n\
{\r\n\
	return getCameraPosition(gViewMatrix);\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot = (float3x3) viewMatrix;\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraDirection()\r\n\
{\r\n\
	return getCameraDirection(gViewMatrix);\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot = (float3x3) viewMatrix;\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraUp()\r\n\
{\r\n\
	return getCameraUp(gViewMatrix);\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot = (float3x3) viewMatrix;\r\n\
	return rot[0];\r\n\
}\r\n\
float3 getCameraRight()\r\n\
{\r\n\
	return getCameraRight(gViewMatrix);\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection, worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection, float3 worldNormal, float3 worldPosition, float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector = normalize(normalize(cameraPosition - worldPosition) + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}";
OverlayShader="#include \"Function.hlsl\"\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
    float3 mPosition : SV_Position;\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
    float4 mPosition : SV_Position;\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
    SVertexShaderOutput output;\r\n\
    output.mPosition = float4(input.mPosition, 1.0);\r\n\
	output.mMainUV = input.mMainUV;\r\n\
	output.mDiffuse = input.mDiffuse;\r\n\
    return output;\r\n\
}\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
SamplerState gDiffuseSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
    float4 mColour : SV_Target;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
    SPixelShaderOutput output = (SPixelShaderOutput) 0;\r\n\
    float3 colour_emissive = input.mDiffuse.rgb;\r\n\
    float alpha = input.mDiffuse.a;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_sampler.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_emissive *= diffuse_texture_colour;\r\n\
#endif\r\n\
    output.mColour.rgb = colour_emissive;\r\n\
    output.mColour.a = alpha;\r\n\
    return output;\r\n\
}";
}