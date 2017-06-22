#include "ForwardShaderCommon.glsl"
in float3 gPositionVS;
#if OUTPUT_WORLD_POSITION
out float3 gWorldPositionPS;
#endif
#if OUTPUT_WORLD_NORMAL
in float3 gNormalVS;
out float3 gWorldNormalPS;
#endif
#if OUTPUT_WORLD_TANGENT
in float3 gTangentVS;
out float3 gWorldTangentPS;
#endif
#if OUTPUT_MAIN_UV
in float2 gMainUVVS;
out float2 gMainUVPS;
#endif
#if OUTPUT_DIFFUSE
in float4 gDiffuseVS;
out float4 gDiffusePS;
#endif
void main()
{
    float4 world_position = mul(gWorldMatrix, float4(gPositionVS, 1.0));
    gl_Position = mul(gViewProjectionMatrix, world_position);
#if OUTPUT_WORLD_POSITION
	gWorldPositionPS = world_position.xyz;
#endif
#if OUTPUT_WORLD_NORMAL
	gWorldNormalPS = mul(float3x3(gWorldMatrix), gNormalVS);
#endif
#if OUTPUT_WORLD_TANGENT
	gWorldTangentPS = mul(float3x3(gWorldMatrix), gTangentVS);
#endif
#if OUTPUT_MAIN_UV
	gMainUVPS = gMainUVVS;
#endif
#if OUTPUT_DIFFUSE
	gDiffusePS = gDiffuseVS;
#endif
}
