#include "Function.hlsl"
#ifndef USE_DIFFUSE_TEXTURE
#define USE_DIFFUSE_TEXTURE 0
#endif
#ifndef USE_FONT_TEXTURE
#define USE_FONT_TEXTURE 0
#endif
in float4 gPositionPS;
in float2 gMainUVPS;
in float4 gDiffusePS;
#if USE_DIFFUSE_TEXTURE || USE_FONT_TEXTURE
uniform sampler2D gDiffuseTexture;
#endif
out float4 gFragColour;
void main()
{
    float3 colour_emissive = gDiffusePS.rgb;
    float alpha = gDiffusePS.a;
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler =texture(gDiffuseTexture, gMainUVPS);
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;
	float diffuse_texture_alpha = diffuse_texture_sampler.a;
	alpha *= diffuse_texture_alpha;
	colour_emissive *= diffuse_texture_colour;
#endif
#if USE_FONT_TEXTURE
	alpha*=texture(gDiffuseTexture,gMainUVPS).r;
#endif
    gFragColour.rgb = colour_emissive;
    gFragColour.a = alpha;
}