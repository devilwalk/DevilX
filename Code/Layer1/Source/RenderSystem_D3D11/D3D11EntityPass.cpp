#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::CEntityPass(CEntityTechnique * technique)
	:mTechnique(technique)
	,mForwardType(CEnum::EForwardPassType_Count)
{
	assert(getTechnique()->getType()!=CEnum::ETechniqueType_Forward);
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_GBufferDS:
		getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndAlphaTestEnableChange);
		getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndColourUnitStateCreate);
		break;
	case CEnum::ETechniqueType_GBufferDL:
		getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndAlphaTestEnableChange);
		getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndLightEnableChange);
		getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndTransparentEnableChange);
		getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndColourUnitStateCreate);
		break;
	}
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_BeginGeometryChange);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndGeometryChange);
	_registerToIGeometryImp();
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::CEntityPass(CEnum::EForwardPassType type,CEntityTechnique * technique)
	:mTechnique(technique)
	,mForwardType(type)
{
	assert(getTechnique()->getType()==CEnum::ETechniqueType_Forward);
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndAlphaTestEnableChange);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndLightEnableChange);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndTransparentEnableChange);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndColourUnitStateCreate);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndTextureUnitStateCreate);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_BeginGeometryChange);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndGeometryChange);
	_registerToIGeometryImp();
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::~CEntityPass()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::onMessage(IEntityRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IEntityRenderableImp::EMessage_BeginGeometryChange:
		_unregisterToIGeometryImp();
		break;
	case IEntityRenderableImp::EMessage_EndGeometryChange:
		_updateShader();
		_registerToIGeometryImp();
		break;
	case IEntityRenderableImp::EMessage_EndAlphaTestEnableChange:
		_updateShader();
		break;
	case IEntityRenderableImp::EMessage_EndLightEnableChange:
		_updateShader();
		break;
	case IEntityRenderableImp::EMessage_EndTransparentEnableChange:
		_updateBlendState();
		break;
	case IEntityRenderableImp::EMessage_EndColourUnitStateCreate:
		_updateShader();
		break;
	case IEntityRenderableImp::EMessage_EndTextureUnitStateCreate:
		static_cast<ITextureUnitStateImp*>(data)->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryImp::EMessage_EndDiffuseEnableChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITextureUnitStateImp::EMessage_EndTextureChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::_updateShader()
{
	if(nullptr==getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
		return;
	const IEntityRenderableImp * const mat_imp=getTechnique()->getMaterial()->getRenderable()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
	{
		CForwardVertexShaderGenerator vs_gen;
		if(mat_imp->getLightEnable()&&(CEnum::EForwardPassType_Ambient!=getForwardType()))
		{
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldNormal);
			if((nullptr!=mat_imp->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular))
				||(CEnum::EForwardPassType_PointLight==getForwardType())
				||(CEnum::EForwardPassType_SpotLight==getForwardType())
				)
			{
				vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldPosition);
			}
		}
		if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry()->getVertexBuffer()->getDiffuses())
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_Diffuse);
		if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry()->getVertexBuffer()->getTextureCoords()
			&&mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)
			&&mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)->getTexture()
			)
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_MainUV);
		mVertexShader=CSystemImp::getSingleton().getVertexShader(vs_gen.generateCode());
		CForwardPixelShaderCodeGenerator ps_gen;
		if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry()->getVertexBuffer()->getTextureCoords()
			&&mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)
			&&mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)->getTexture()
			)
			ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseDiffuseTexture);
		if(mat_imp->getLightEnable())
		{
			ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseLighting);
			if(CEnum::EForwardPassType_Ambient!=getForwardType())
			{
				switch(getForwardType())
				{
				case CEnum::EForwardPassType_DirectionLight:
					ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseDirectionLight);
					break;
				case CEnum::EForwardPassType_PointLight:
					ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UsePointLight);
					break;
				case CEnum::EForwardPassType_SpotLight:
					ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseSpotLight);
					break;
				}
				if(mat_imp->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular))
				{
					ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseSpecular);
				}
			}
		}
		if(mat_imp->isAlphaTestEnable())
		{
			ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseAlphaTest);
		}
		auto macros=vs_gen.generateMacro();
		mPixelShader=CSystemImp::getSingleton().getPixelShader(ps_gen.generateCode(&macros));
	}
	break;
	}
	_updateTextures();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::_updateTextures()
{
	const IEntityRenderableImp * const mat_imp=getTechnique()->getMaterial()->getRenderable()->getInterfaceImp();
	mVSTextures.clear();
	mPSTextures.clear();
	if(0xffffffff!=getVertexShader()->getSlot("gDiffuseTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getVertexShader()->getSlot("gNormalTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Normal)->getTexture())));
	}
	if(0xffffffff!=getPixelShader()->getSlot("gDiffuseTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getPixelShader()->getSlot("gNormalTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Normal)->getTexture())));
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::_updateRasterizerState()
{
	D3D11_RASTERIZER_DESC1 desc=CSystemImp::getSingleton().getDefaultRasterizerStateDescription();
	const IEntityRenderableImp * const mat_imp=getTechnique()->getMaterial()->getRenderable()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		break;
	}
	mRasterizerState=CSystemImp::getSingleton().getRasterizerState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::_updateBlendState()
{
	D3D11_BLEND_DESC1 desc=CSystemImp::getSingleton().getDefaultBlendStateDescription();
	const IEntityRenderableImp * const mat_imp=getTechnique()->getMaterial()->getRenderable()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		if(mat_imp->getTransparentEnable())
		{
			desc.RenderTarget[0].BlendEnable=TRUE;
			desc.RenderTarget[0].DestBlend=D3D11_BLEND_INV_SRC_ALPHA;
			desc.RenderTarget[0].SrcBlend=D3D11_BLEND_SRC_ALPHA;
		}
		else
		{
			switch(getForwardType())
			{
			case CEnum::EForwardPassType_Ambient:
				break;
			default:
				desc.RenderTarget[0].BlendEnable=TRUE;
				desc.RenderTarget[0].DestBlend=D3D11_BLEND_ONE;
				desc.RenderTarget[0].SrcBlend=D3D11_BLEND_ONE;
			}
		}
		break;
	}
	mBlendState=CSystemImp::getSingleton().getBlendState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::_updateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC desc=CSystemImp::getSingleton().getDefaultDepthStencilDescription();
	const IEntityRenderableImp * const mat_imp=getTechnique()->getMaterial()->getRenderable()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		if(mat_imp->getTransparentEnable())
		{
			desc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ZERO;
			desc.DepthFunc=D3D11_COMPARISON_LESS_EQUAL;
		}
		else
		{
			switch(getForwardType())
			{
			case CEnum::EForwardPassType_Ambient:
				desc.DepthFunc=D3D11_COMPARISON_LESS_EQUAL;
				break;
			default:
				desc.DepthFunc=D3D11_COMPARISON_EQUAL;
				desc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ZERO;
			}
		}
		break;
	}
	mDepthState=CSystemImp::getSingleton().getDepthStencilState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::_registerToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())->addListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::_unregisterToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())->removeListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}
