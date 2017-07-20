#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::CEntityForwardPass(CEntityTechnique * technique)
	:CEntityPass(technique)
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
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaTestEnableChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndColourUnitStateCreate);
		break;
	case CEnum::ETechniqueType_GBufferDL:
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaTestEnableChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndLightEnableChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndTransparentEnableChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndColourUnitStateCreate);
		break;
	}
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_BeginGeometryChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndGeometryChange);
	_registerToIGeometryImp();
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::CEntityForwardPass(CEnum::EForwardPassType type,CEntityTechnique * technique)
	:CEntityPass(technique)
	,mForwardType(type)
{
	assert(getTechnique()->getType()==CEnum::ETechniqueType_Forward);
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaTestEnableChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndLightEnableChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndTransparentEnableChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndColourUnitStateCreate);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndTextureUnitStateCreate);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_BeginGeometryChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndGeometryChange);
	_registerToIGeometryImp();
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::~CEntityForwardPass()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISubEntityImp::EMessage_BeginGeometryChange:
		_unregisterToIGeometryImp();
		break;
	case ISubEntityImp::EMessage_EndGeometryChange:
		_updateShader();
		_registerToIGeometryImp();
		break;
	case ISubEntityImp::EMessage_EndAlphaTestEnableChange:
		_updateShader();
		break;
	case ISubEntityImp::EMessage_EndLightEnableChange:
		_updateShader();
		break;
	case ISubEntityImp::EMessage_EndTransparentEnableChange:
		_updateBlendState();
		break;
	case ISubEntityImp::EMessage_EndColourUnitStateCreate:
		_updateShader();
		break;
	case ISubEntityImp::EMessage_EndTextureUnitStateCreate:
		static_cast<ITextureUnitStateImp*>(data)->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryImp::EMessage_EndDiffuseEnableChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITextureUnitStateImp::EMessage_EndTextureChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateShader()
{
	if(nullptr==getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())
		return;
	const ISubEntityImp * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
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
		if(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry()->getVertexBuffer()->getDiffuses())
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_Diffuse);
		if(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry()->getVertexBuffer()->getTextureCoords()
			&&mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)
			&&mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)->getTexture()
			)
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_MainUV);
		mVertexShader=CSystemImp::getSingleton().getVertexShader(vs_gen.generateCode());
		CForwardPixelShaderCodeGenerator ps_gen;
		if(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry()->getVertexBuffer()->getTextureCoords()
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

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateTextures()
{
	const ISubEntityImp * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
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

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateRasterizerState()
{
	D3D11_RASTERIZER_DESC1 desc=CSystemImp::getSingleton().getDefaultRasterizerStateDescription();
	const ISubEntityImp * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		break;
	}
	mRasterizerState=CSystemImp::getSingleton().getRasterizerState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateBlendState()
{
	D3D11_BLEND_DESC1 desc=CSystemImp::getSingleton().getDefaultBlendStateDescription();
	const ISubEntityImp * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
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

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC desc=CSystemImp::getSingleton().getDefaultDepthStencilDescription();
	const ISubEntityImp * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
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

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_registerToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())->addListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_unregisterToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())->removeListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}
