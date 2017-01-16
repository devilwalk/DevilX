#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::CClearViewportShader()
{
	mVertexShader=CSystemImp::getSingleton().getVertexShader(_generateVertexShaderCode());
	mPixelShader=CSystemImp::getSingleton().getPixelShader(_generatePixelShaderCode());
	for(auto i=0;i<EDepthStencilStateType_Count;++i)
		_generateDepthStencilState((EDepthStencilStateType)i);
	for(auto i=0;i<EBlendStateType_Count;++i)
		_generateBlendState((EBlendStateType)i);
	_generateRasterizerState();
}

NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::~CClearViewportShader()
{
}

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::_generateVertexShaderCode() const
{
	String code_key="ClearViewport_VertexShader";
	ID3DBlob * ret=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==ret)
	{
		switch(CSystemImp::getSingleton().getShaderModelType())
		{
		case CEnum::EShaderModelType_4_1:
			ret=CSystemImp::getSingleton().getShaderCodeManager()->registerVertexShader(code_key,CSystemImp::getSingleton().getDefinitionShader4_1()->ClearViewport,CSystemImp::getSingleton().getShaderModelType(),nullptr);
			break;
		case CEnum::EShaderModelType_5:
			ret=CSystemImp::getSingleton().getShaderCodeManager()->registerVertexShader(code_key,CSystemImp::getSingleton().getDefinitionShader5()->ClearViewport,CSystemImp::getSingleton().getShaderModelType(),nullptr);
			break;
		}
	}
	return ret;
}

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::_generatePixelShaderCode() const
{
	String code_key="ClearViewportPixelShader";
	ID3DBlob * ret=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==ret)
	{
		switch(CSystemImp::getSingleton().getShaderModelType())
		{
		case CEnum::EShaderModelType_4_1:
			ret=CSystemImp::getSingleton().getShaderCodeManager()->registerPixelShader(code_key,CSystemImp::getSingleton().getDefinitionShader4_1()->ClearViewport,CSystemImp::getSingleton().getShaderModelType(),nullptr);
			break;
		case CEnum::EShaderModelType_5:
			ret=CSystemImp::getSingleton().getShaderCodeManager()->registerPixelShader(code_key,CSystemImp::getSingleton().getDefinitionShader5()->ClearViewport,CSystemImp::getSingleton().getShaderModelType(),nullptr);
			break;
		}
	}
	return ret;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::_generateDepthStencilState(EDepthStencilStateType type)
{
	auto desc=CSystemImp::getSingleton().getDefaultDepthStencilDescription();
	desc.DepthFunc=D3D11_COMPARISON_ALWAYS;
	switch(type)
	{
	case EDepthStencilStateType_WriteDepthOnly:
		break;
	case EDepthStencilStateType_WriteStencilOnly:
		desc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.StencilEnable=TRUE;
		desc.FrontFace.StencilFunc=D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp=D3D11_STENCIL_OP_REPLACE;
		desc.FrontFace.StencilFailOp=D3D11_STENCIL_OP_REPLACE;
		desc.FrontFace.StencilDepthFailOp=D3D11_STENCIL_OP_REPLACE;
		desc.BackFace.StencilFunc=D3D11_COMPARISON_ALWAYS;
		desc.BackFace.StencilPassOp=D3D11_STENCIL_OP_REPLACE;
		desc.BackFace.StencilFailOp=D3D11_STENCIL_OP_REPLACE;
		desc.BackFace.StencilDepthFailOp=D3D11_STENCIL_OP_REPLACE;
		break;
	case EDepthStencilStateType_WriteAll:
		desc.StencilEnable=TRUE;
		desc.FrontFace.StencilFunc=D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp=D3D11_STENCIL_OP_REPLACE;
		desc.FrontFace.StencilFailOp=D3D11_STENCIL_OP_REPLACE;
		desc.FrontFace.StencilDepthFailOp=D3D11_STENCIL_OP_REPLACE;
		desc.BackFace.StencilFunc=D3D11_COMPARISON_ALWAYS;
		desc.BackFace.StencilPassOp=D3D11_STENCIL_OP_REPLACE;
		desc.BackFace.StencilFailOp=D3D11_STENCIL_OP_REPLACE;
		desc.BackFace.StencilDepthFailOp=D3D11_STENCIL_OP_REPLACE;
		break;
	case EDepthStencilStateType_Null:
		desc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ZERO;
		break;
	}
	mDepthStencilState[type]=CSystemImp::getSingleton().getDepthStencilState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::_generateBlendState(EBlendStateType type)
{
	auto desc=CSystemImp::getSingleton().getDefaultBlendStateDescription();
	switch(type)
	{
	case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EBlendStateType_WriteColour:
		break;
	case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EBlendStateType_Null:
		for(auto i=0;i<8;++i)
			desc.RenderTarget[i].RenderTargetWriteMask=0;
		break;
	}
	mBlendState[type]=CSystemImp::getSingleton().getBlendState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::_generateRasterizerState()
{
	auto desc=CSystemImp::getSingleton().getDefaultRasterizerStateDescription();
	desc.CullMode=D3D11_CULL_NONE;
	desc.DepthClipEnable=FALSE;
	mRasterizerState=CSystemImp::getSingleton().getRasterizerState(desc);
}
