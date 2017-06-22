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
cbuffer cbScene
{
    float3 gAmbientColour;
};