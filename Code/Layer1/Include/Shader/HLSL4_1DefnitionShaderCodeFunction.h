#pragma once
namespace NSDevilX
{
namespace NSRenderSystem
{
namespace NSHLSL4_1
{
class CDefinitionShader:public TBaseObject<CDefinitionShader>{
public:
String ClearViewport;
String ConstantBuffer;
String DeferredLightingGBufferShader;
String DeferredShadingGBufferShader;
String ForwardShader;
String Function;
String OverlayShader;
CDefinitionShader();
};
}
}
}