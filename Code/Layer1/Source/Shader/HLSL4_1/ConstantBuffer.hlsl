cbuffer cbSystem
{
    float gFrameTimeInSeconds : packoffset(c0);
    float gInverseFrameTimeInSeconds : packoffset(c0.y);
};
cbuffer cbRenderTarget
{
    float2 gRenderTargetSizeInPixel : packoffset(c0);
    float2 gInverseRenderTargetSizeInPixel : packoffset(c0.z);
};
cbuffer cbViewport
{
    float2 gViewportSizeInPixel : packoffset(c0);
    float2 gInverseViewportSizeInPixel : packoffset(c0.z);
};
cbuffer cbCamera
{
    float4x4 gViewMatrix : packoffset(c0);
    float4x4 gInverseViewMatrix : packoffset(c4);
    float4x4 gProjectionMatrix : packoffset(c8);
    float4x4 gInverseProjectionMatrix : packoffset(c12);
    float4x4 gViewProjectionMatrix : packoffset(c16);
    float4x4 gInverseViewProjectionMatrix : packoffset(c20);
    float gFarDistance : packoffset(c24);
    float gInverseFarDistance : packoffset(c24.y);
};
cbuffer cbDirectionLight
{
    float3 gDirectionLightDiffuseColour : packoffset(c0);
    float3 gDirectionLightSpecularColour : packoffset(c1);
    float3 gDirectionLightDirection : packoffset(c2);
};
cbuffer cbPointLight
{
    float3 gPointLightDiffuseColour : packoffset(c0);
    float3 gPointLightSpecularColour : packoffset(c1);
    float3 gPointLightPosition : packoffset(c2);
    float gPointLightReciprocalRange : packoffset(c0.w);
    float gPointLightStartFallOffDistance : packoffset(c1.w);
};
cbuffer cbSpotLight
{
    float3 gSpotLightDiffuseColour : packoffset(c0);
    float3 gSpotLightSpecularColour : packoffset(c1);
    float3 gSpotLightDirection : packoffset(c2);
    float3 gSpotLightPosition : packoffset(c3);
    float gSpotLightReciprocalRange : packoffset(c0.w);
    float gSpotLightStartFallOffDistance : packoffset(c1.w);
    float gSpotLightCosInnerCornerHalfAngle : packoffset(c2.w);
    float gSpotLightReciprocalDeltaCosHalfAngle : packoffset(c3.w);
};
cbuffer cbScene
{
    float3 gAmbientColour : packoffset(c0);
};
cbuffer cbObjectTransform
{
    float4x4 gWorldMatrix : packoffset(c0);
};
cbuffer cbObjectMaterial
{
    float3 gMainColour : packoffset(c0);
    float gAlpha : packoffset(c0.w);
    float3 gSpecularColour : packoffset(c1);
    float gSpecularPower : packoffset(c1.w);
    float3 gEmissiveColour : packoffset(c2);
    float gAlphaTestValue : packoffset(c2.w);
};