#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CPass::CPass(CTechnique * technique)
	:mTechnique(technique)
	,mForwardType(CEnum::EForwardPassType_Count)
	,mVertexShader(nullptr)
	,mPixelShader(nullptr)
	,mRasterizerState(nullptr)
	,mBlendState(nullptr)
	,mDepthState(nullptr)
{
	assert(getTechnique()->getType()!=CEnum::ETechniqueType_Forward);
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_GBufferDS:
		getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndAlphaTestEnableChange);
		getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndColourUnitStateCreate);
		break;
	case CEnum::ETechniqueType_GBufferDL:
		getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndAlphaTestEnableChange);
		getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndLightEnableChange);
		getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndTransparentEnableChange);
		getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndColourUnitStateCreate);
		break;
	}
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IRenderableImp>*>(this),IRenderableImp::EMessage_BeginGeometryChange);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IRenderableImp>*>(this),IRenderableImp::EMessage_EndGeometryChange);
	_registerToIGeometryImp();
}

NSDevilX::NSRenderSystem::NSD3D11::CPass::CPass(CEnum::EForwardPassType type,CTechnique * technique)
	:mTechnique(technique)
	,mForwardType(type)
	,mVertexShader(nullptr)
	,mPixelShader(nullptr)
	,mRasterizerState(nullptr)
	,mBlendState(nullptr)
	,mDepthState(nullptr)
{
	assert(getTechnique()->getType()==CEnum::ETechniqueType_Forward);
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
	getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndAlphaTestEnableChange);
	getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndLightEnableChange);
	getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndTransparentEnableChange);
	getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndColourUnitStateCreate);
	getTechnique()->getMaterial()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndTextureUnitStateCreate);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IRenderableImp>*>(this),IRenderableImp::EMessage_BeginGeometryChange);
	getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IRenderableImp>*>(this),IRenderableImp::EMessage_EndGeometryChange);
	_registerToIGeometryImp();
}

NSDevilX::NSRenderSystem::NSD3D11::CPass::~CPass()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::onMessage(IMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IMaterialImp::EMessage_EndAlphaTestEnableChange:
		_updateShader();
		break;
	case IMaterialImp::EMessage_EndLightEnableChange:
		_updateShader();
		break;
	case IMaterialImp::EMessage_EndTransparentEnableChange:
		_updateBlendState();
		break;
	case IMaterialImp::EMessage_EndColourUnitStateCreate:
		_updateShader();
		break;
	case IMaterialImp::EMessage_EndTextureUnitStateCreate:
		static_cast<ITextureUnitStateImp*>(data)->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IRenderableImp::EMessage_BeginGeometryChange:
		_unregisterToIGeometryImp();
		break;
	case IRenderableImp::EMessage_EndGeometryChange:
		_updateShader();
		_registerToIGeometryImp();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryImp::EMessage_EndDiffuseEnableChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITextureUnitStateImp::EMessage_EndTextureChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::_updateShader()
{
	if(nullptr==getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
		return;
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
	{
		CForwardVertexShaderGenerator vs_gen;
		if(mat_imp->getLightEnable()&&(CEnum::EForwardPassType_Ambient!=getForwardType()))
		{
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldNormal);
			if((nullptr!=mat_imp->getColourUnitState(IEnum::EColourUnitStateType_Specular))
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
			&&mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)
			&&mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)->getTexture()
			)
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_MainUV);
		mVertexShader=CSystemImp::getSingleton().getVertexShader(vs_gen.generateCode());
		CForwardPixelShaderCodeGenerator ps_gen;
		if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry()->getVertexBuffer()->getTextureCoords()
			&&mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)
			&&mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)->getTexture()
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
				if(mat_imp->getColourUnitState(IEnum::EColourUnitStateType_Specular))
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

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::_updateTextures()
{
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
	mVSTextures.clear();
	mPSTextures.clear();
	if(0xffffffff!=getVertexShader()->getSlot("gDiffuseTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getVertexShader()->getSlot("gNormalTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Normal)->getTexture())));
	}
	if(0xffffffff!=getPixelShader()->getSlot("gDiffuseTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getPixelShader()->getSlot("gNormalTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Normal)->getTexture())));
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::_updateRasterizerState()
{
	D3D11_RASTERIZER_DESC1 desc=CSystemImp::getSingleton().getDefaultRasterizerStateDescription();
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		break;
	}
	mRasterizerState=CSystemImp::getSingleton().getRasterizerState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::_updateBlendState()
{
	D3D11_BLEND_DESC1 desc=CSystemImp::getSingleton().getDefaultBlendStateDescription();
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
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

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::_updateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC desc=CSystemImp::getSingleton().getDefaultDepthStencilDescription();
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
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

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::_registerToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())->addListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CPass::_unregisterToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())->removeListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}
