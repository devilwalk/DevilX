#include "Function.hlsl"
in float3 gPositionVS;
in float2 gMainUVVS;
in float4 gDiffuseVS;
out float2 gMainUVPS;
out float4 gDiffusePS;
void main()
{
    gl_Position = float4(gPositionVS, 1.0);
	gMainUVPS = gMainUVVS;
	gDiffusePS = gDiffuseVS;
}
