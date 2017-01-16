#pragma once
namespace NSDevilX
{
namespace NSRenderSystem
{
namespace NSGLSL4_5
{
class CDefinitionShader:public TBaseObject<CDefinitionShader>{
public:
String ClearViewportPixel;
String ClearViewportVertex;
String ConstantBuffer;
String DeferredLightingGBufferShader;
String DeferredShadingGBufferShader;
String Defines;
String ForwardShaderCommon;
String ForwardShaderPixel;
String ForwardShaderVertex;
String Function;
CDefinitionShader();
};
}
}
}