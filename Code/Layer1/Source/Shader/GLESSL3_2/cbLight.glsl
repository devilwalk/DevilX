#include "Defines.glsl"
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
