#include "OverlayShader.sl"
in float3 gPositionVS;
in float2 gMainUVVS;
in float4 gDiffuseVS;
out float2 gMainUVPS;
out float4 gDiffusePS;
void main()
{
#define iPosition gPositionVS
#define iMainUV gMainUVVS
#define iDiffuse gDiffuseVS
#define oPosition gl_Position
#define oMainUV gMainUVPS
#define oDiffuse gDiffusePS
#include "OverlayVertexShaderCode.sl"
}
