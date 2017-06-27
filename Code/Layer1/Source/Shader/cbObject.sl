#include "Defines.sl"
DECL_CB(cbObjectTransform)
CB_MEMBER float4x4 gWorldMatrix;
END_DECL
DECL_CB(cbObjectMaterial)
CB_MEMBER float3 gMainColour;
CB_MEMBER float gAlpha;
CB_MEMBER float3 gSpecularColour;
CB_MEMBER float gSpecularPower;
CB_MEMBER float3 gEmissiveColour;
CB_MEMBER float gAlphaTestValue;
END_DECL