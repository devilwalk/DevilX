#include "Defines.glsl"
cbuffer cbSystem
{
    float gFrameTimeInSeconds;
    float gInverseFrameTimeInSeconds;
};
cbuffer cbRenderTarget
{
    float2 gRenderTargetSizeInPixel;
    float2 gInverseRenderTargetSizeInPixel;
};
cbuffer cbViewport
{
    float2 gViewportSizeInPixel;
    float2 gInverseViewportSizeInPixel;
};
cbuffer cbCamera
{
    float4x4 gViewMatrix;
    float4x4 gInverseViewMatrix;
    float4x4 gProjectionMatrix;
    float4x4 gInverseProjectionMatrix;
    float4x4 gViewProjectionMatrix;
    float4x4 gInverseViewProjectionMatrix;
    float gFarDistance;
    float gInverseFarDistance;
};
cbuffer cbShadowMap0
{
    float4x4 gShadowMap0ViewProjectionMatrix;
    float gShadowMap0FarDistance;
    float gShadowMap0InverseFarDistance;
};
cbuffer cbShadowMap1
{
    float4x4 gShadowMap1ViewProjectionMatrix;
    float gShadowMap1FarDistance;
    float gShadowMap1InverseFarDistance;
};
cbuffer cbShadowMap2
{
    float4x4 gShadowMap2ViewProjectionMatrix;
    float gShadowMap2FarDistance;
    float gShadowMap2InverseFarDistance;
};
cbuffer cbShadowMap3
{
    float4x4 gShadowMap3ViewProjectionMatrix;
    float gShadowMap3FarDistance;
    float gShadowMap3InverseFarDistance;
};
cbuffer cbDirectionLight
{
    float3 gDirectionLightDiffuseColour;
    float3 gDirectionLightSpecularColour;
    float3 gDirectionLightDirection;
};
cbuffer cbPointLight
{
    float3 gPointLightDiffuseColour;
    float3 gPointLightSpecularColour;
    float3 gPointLightPosition;
    float gPointLightReciprocalRange;
    float gPointLightStartFallOffDistance;
};
cbuffer cbSpotLight
{
    float3 gSpotLightDiffuseColour;
    float3 gSpotLightSpecularColour;
    float3 gSpotLightDirection;
    float3 gSpotLightPosition;
    float gSpotLightReciprocalRange;
    float gSpotLightStartFallOffDistance;
    float gSpotLightCosInnerCornerHalfAngle;
    float gSpotLightReciprocalDeltaCosHalfAngle;
};
cbuffer cbScene
{
    float3 gAmbientColour;
};
cbuffer cbObjectTransform
{
    float4x4 gWorldMatrix;
};
cbuffer cbObjectMaterial
{
    float3 gMainColour;
    float gAlpha;
    float3 gSpecularColour;
    float gSpecularPower;
    float3 gEmissiveColour;
    float gAlphaTestValue;
};