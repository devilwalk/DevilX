#include "ForwardShader.sl"
#if OUTPUT_WORLD_POSITION
in float3 gWorldPositionPS;
#endif
#if OUTPUT_WORLD_NORMAL
in float3 gWorldNormalPS;
#endif
#if OUTPUT_WORLD_TANGENT
in float3 gWorldTangentPS;
#endif
#if OUTPUT_MAIN_UV
in float2 gMainUVPS;
#endif
#if OUTPUT_DIFFUSE
in float4 gDiffusePS;
#endif
sampler2D gDiffuseTexture;
sampler2D gNormalTexture;
out float4 gFragColour;
void main()
{
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler=texture(gDiffuseTexture,input.mMainUV);
#endif
#if USE_NORMAL_TEXTURE
	float4 normal_texture_sampler=texture(gNormalTexture,input.mMainUV);
#endif
#define iWorldPosition gWorldPositionPS
#define iWorldNormal gWorldNormalPS
#define iWorldTangent gWorldTangentPS
#define iMainUV gMainUVPS
#define iDiffuse gDiffusePS
#define oColour gFragColour
#include "ForwardPixelShaderCode.sl"
}