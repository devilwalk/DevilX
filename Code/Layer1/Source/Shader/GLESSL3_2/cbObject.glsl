#include "Defines.glsl"
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