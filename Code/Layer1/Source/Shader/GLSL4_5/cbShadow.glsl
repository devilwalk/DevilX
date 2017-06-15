#include "Defines.glsl"
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
