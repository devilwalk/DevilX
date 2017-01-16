#pragma once
namespace NSDevilX
{
namespace NSRenderSystem
{
namespace NSHLSL5
{
class CDefinitionShader:public TBaseObject<CDefinitionShader>{
public:
String CascadedShadowMap;
String ClearViewport;
String ConstantBuffer;
String DeferredLightingGBufferShader;
String DeferredShadingGBufferShader;
String ForwardShader;
String Function;
CDefinitionShader();
};
}
}
}