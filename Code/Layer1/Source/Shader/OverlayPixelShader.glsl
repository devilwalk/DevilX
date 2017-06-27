#include "OverlayShader.sl"
in float4 gPositionPS;
in float2 gMainUVPS;
in float4 gDiffusePS;
#ifndef USE_FONT_TEXTURE
#define USE_FONT_TEXTURE 0
#endif
#if USE_DIFFUSE_TEXTURE || USE_FONT_TEXTURE
uniform sampler2D gDiffuseTexture;
#endif
out float4 gFragColour;
void main()
{
#if USE_FONT_TEXTURE||USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler=texture(gDiffuseTexture,gMainUVPS);
#endif
#define iDiffuse gDiffusePS
#define oColour gFragColour
#include "OverlayPixelShaderCode.sl"
}