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
CB_MEMBER float gMetallic;
CB_MEMBER float gRoughness;
CB_MEMBER float gOrenNayar_A;
CB_MEMBER float gOrenNayar_B;
END_DECL