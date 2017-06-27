#include "ForwardShader.sl"
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
#define iPosition gPositionVS
#define iNormal gNormalVS
#define iTangent gTangentVS
#define iMainUV gMainUVVS
#define iDiffuse gDiffuseVS
#define oPosition gl_Position
#define oWorldPosition gWorldPositionPS
#define oWorldNormal gWorldNormalPS
#define oWorldTangent gWorldTangentPS
#define oMainUV gMainUVPS
#define oDiffuse gDiffusePS
#include "ForwardVertexShaderCode.sl"
}
