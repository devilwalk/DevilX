#pragma once
namespace NSDevilX
{
namespace NSRenderSystem
{
class CDefinitionShader:public TBaseObject<CDefinitionShader>{
public:
String ClearViewport_hlsl;
String ClearViewportPixel_glsl;
String ClearViewportVertex_glsl;
String ForwardPixelShader_glsl;
String ForwardShader_hlsl;
String ForwardVertexShader_glsl;
String OverlayPixelShader_glsl;
String OverlayShader_hlsl;
String OverlayVertexShader_glsl;
CDefinitionShader();
};
}
}