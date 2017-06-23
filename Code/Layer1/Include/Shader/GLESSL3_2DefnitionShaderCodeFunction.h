#pragma once
namespace NSDevilX
{
namespace NSRenderSystem
{
namespace NSGLESSL3_2
{
class CDefinitionShader:public TBaseObject<CDefinitionShader>{
public:
String cbLight;
String cbObject;
String cbShadow;
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
String FunctionEx;
String OverlayShaderPixel;
String OverlayShaderVertex;
CDefinitionShader();
};
}
}
}