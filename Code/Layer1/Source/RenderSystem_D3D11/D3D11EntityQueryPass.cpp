#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::CEntityQueryPass(CEntityTechnique * technique)
	:CEntityPass(technique)
{
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
	_updateSamplerState();
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaTestEnableChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndTransparentEnableChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaColourCreate);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndDiffuseTextureCreate);
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::~CEntityQueryPass()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::_updateShader()
{
	String code_key="Ouery_VertexShader";
	ID3DBlob * blob=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==blob)
	{
		blob=CSystemImp::getSingleton().getShaderCodeManager()->registerShader(code_key,ISystemImp::getSingleton().getDefinitionShader()->QueryShader_hlsl,CEnum::EShaderType_VertexShader,CSystemImp::getSingleton().getShaderModelType(),nullptr);
	}
	mVertexShader=CSystemImp::getSingleton().getVertexShader(blob);

	code_key="Ouery_PixelShader";
	blob=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==blob)
	{
		blob=CSystemImp::getSingleton().getShaderCodeManager()->registerShader(code_key,ISystemImp::getSingleton().getDefinitionShader()->QueryShader_hlsl,CEnum::EShaderType_PixelShader,CSystemImp::getSingleton().getShaderModelType(),nullptr);
	}
	mPixelShader=CSystemImp::getSingleton().getPixelShader(blob);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::_updateRasterizerState()
{
	D3D11_RASTERIZER_DESC1 desc=CSystemImp::getSingleton().getDefaultRasterizerStateDescription();
	desc.ScissorEnable=TRUE;
	mRasterizerState=CSystemImp::getSingleton().getRasterizerState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::_updateBlendState()
{
	D3D11_BLEND_DESC1 desc=CSystemImp::getSingleton().getDefaultBlendStateDescription();
	mBlendState=CSystemImp::getSingleton().getBlendState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::_updateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC desc=CSystemImp::getSingleton().getDefaultDepthStencilDescription();
	mDepthState=CSystemImp::getSingleton().getDepthStencilState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::_updateSamplerState()
{
	mPSSamplerStates.clear();
	D3D11_SAMPLER_DESC desc=CSystemImp::getSingleton().getDefaultSamplerStateDescription();
	desc.AddressU=D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV=D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter=D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	mPSSamplerStates.push_back(CSystemImp::getSingleton().getSamplerState(desc));
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISubEntityImp::EMessage_EndAlphaTestEnableChange:
		_updateShader();
		break;
	case ISubEntityImp::EMessage_EndTransparentEnableChange:
		_updateBlendState();
		break;
	case ISubEntityImp::EMessage_EndAlphaColourCreate:
		_updateShader();
		break;
	case ISubEntityImp::EMessage_EndDiffuseTextureCreate:
		static_cast<ITextureUnitStateImp*>(data)->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITextureUnitStateImp::EMessage_EndTextureChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryPass::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}
