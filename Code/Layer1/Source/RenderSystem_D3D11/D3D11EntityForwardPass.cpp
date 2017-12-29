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
		break;
	case CEnum::ETechniqueType_GBufferDL:
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaTestEnableChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAmbientModelChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndDiffuseModelChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndSpecularModelChange);
		getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndTransparentEnableChange);
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
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAmbientModelChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndDiffuseModelChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndSpecularModelChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndTransparentEnableChange);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndDiffuseTextureCreate);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndSpecularTextureCreate);
	getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndNormalTextureCreate);
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
	case ISubEntityImp::EMessage_EndAmbientModelChange:
	case ISubEntityImp::EMessage_EndDiffuseModelChange:
	case ISubEntityImp::EMessage_EndSpecularModelChange:
		_updateShader();
		break;
	case ISubEntityImp::EMessage_EndTransparentEnableChange:
		_updateBlendState();
		break;
	case ISubEntityImp::EMessage_EndDiffuseTextureCreate:
		notifier->getDiffuseTexture()->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
		break;
	case ISubEntityImp::EMessage_EndSpecularTextureCreate:
		notifier->getSpecularTexture()->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
		break;
	case ISubEntityImp::EMessage_EndNormalTextureCreate:
		notifier->getNormalTexture()->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
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
	switch(mForwardType)
	{
	case CEnum::EForwardPassType_Ambient:_updateAmbientAndNoLightShader();break;
	case CEnum::EForwardPassType_DirectionLight:
	case CEnum::EForwardPassType_PointLight:
	case CEnum::EForwardPassType_SpotLight:
		if((getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getDiffuseModel()!=IEnum::EMaterialDiffuseModel_None)||(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getSpecularModel()!=IEnum::EMaterialSpecularModel_None))
			_updateLightShader();
		break;
	}
	if(mVertexShader&&mPixelShader)
		_updateTextures();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateAmbientAndNoLightShader()
{
	const auto sub_entity_interface=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
	auto ambient_model=sub_entity_interface->getAmbientModel();
	if((ambient_model!=IEnum::EMaterialAmbientModel_None)&&
		((!sub_entity_interface->getGeometry()->getVertexBuffer()->getNormals())||(!sub_entity_interface->getGeometry()->getVertexBuffer()->getTextureCoords())))
	{
		ambient_model=IEnum::EMaterialAmbientModel_Constant;
	}
	CForwardVertexShaderGenerator vs_gen;
	if((ambient_model==IEnum::EMaterialAmbientModel_Hemisphere)
		||(ambient_model==IEnum::EMaterialAmbientModel_SphericalHarmonics)
		)
	{
		vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldNormal);
		if(sub_entity_interface->getNormalTexture()&&sub_entity_interface->getNormalTexture()->getTexture())
		{
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_MainUV);
		}
	}
	if(sub_entity_interface->getGeometry()->getVertexBuffer()->getTextureCoords()&&sub_entity_interface->getDiffuseTexture()&&sub_entity_interface->getDiffuseTexture()->getTexture())
	{
		vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_MainUV);
	}
	if(sub_entity_interface->getGeometry()->getVertexBuffer()->getDiffuses())
		vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_Diffuse);
	mVertexShader=CSystemImp::getSingleton().getVertexShader(vs_gen.generateCode());
	CForwardPixelShaderCodeGenerator ps_gen;
	switch(ambient_model)
	{
	case IEnum::EMaterialAmbientModel_Constant:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseConstantAmbientModel);break;
	case IEnum::EMaterialAmbientModel_Hemisphere:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseHemisphereAmbientModel);break;
	case IEnum::EMaterialAmbientModel_SphericalHarmonics:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseSphericalHarmonicsAmbientModel);break;
	}
	if(sub_entity_interface->isAlphaTestEnable())
	{
		ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseAlphaTest);
	}
	if(sub_entity_interface->getGeometry()->getVertexBuffer()->getTextureCoords()&&sub_entity_interface->getDiffuseTexture()&&sub_entity_interface->getDiffuseTexture()->getTexture())
	{
		ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseDiffuseTexture);
	}
	auto macros=vs_gen.generateMacro();
	mPixelShader=CSystemImp::getSingleton().getPixelShader(ps_gen.generateCode(&macros));
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateLightShader()
{
	const auto sub_entity_interface=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
	CForwardVertexShaderGenerator vs_gen;
	vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldNormal);
	if(sub_entity_interface->getGeometry()->getVertexBuffer()->getTextureCoords())
	{
		if(((sub_entity_interface->getDiffuseTexture()&&sub_entity_interface->getDiffuseTexture()->getTexture())||
			(sub_entity_interface->getNormalTexture()&&sub_entity_interface->getNormalTexture()->getTexture())))
		{
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_MainUV);
		}
		if((sub_entity_interface->getSpecularModel()!=IEnum::EMaterialSpecularModel_None)&&sub_entity_interface->getSpecularTexture()&&sub_entity_interface->getSpecularTexture()->getTexture())
		{
			vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_MainUV);
		}
	}
	switch(sub_entity_interface->getDiffuseModel())
	{
	case IEnum::EMaterialDiffuseModel_OrenNayar:
	case IEnum::EMaterialDiffuseModel_Minnaert:
	case IEnum::EMaterialDiffuseModel_Disney:
		vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldPosition);
		break;
	}
	switch(mForwardType)
	{
	case CEnum::EForwardPassType_PointLight:
	case CEnum::EForwardPassType_SpotLight:vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldPosition);break;
	}
	if(sub_entity_interface->getSpecularModel()!=IEnum::EMaterialSpecularModel_None)
	{
		vs_gen.addOutput(CForwardVertexShaderGenerator::EOutput_WorldPosition);
	}
	mVertexShader=CSystemImp::getSingleton().getVertexShader(vs_gen.generateCode());
	CForwardPixelShaderCodeGenerator ps_gen;
	switch(mForwardType)
	{
	case CEnum::EForwardPassType_DirectionLight:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseDirectionLight);break;
	case CEnum::EForwardPassType_PointLight:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UsePointLight);break;
	case CEnum::EForwardPassType_SpotLight:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseSpotLight);break;
	}
	switch(sub_entity_interface->getDiffuseModel())
	{
	case IEnum::EMaterialDiffuseModel_Lambert:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseLambertDiffuseModel);break;
	case IEnum::EMaterialDiffuseModel_OrenNayar:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseOrenNayarDiffuseModel);break;
	case IEnum::EMaterialDiffuseModel_Minnaert:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseMinnaertDiffuseModel);break;
	case IEnum::EMaterialDiffuseModel_Disney:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseDisneyDiffuseModel);break;
	}
	switch(sub_entity_interface->getSpecularModel())
	{
	case IEnum::EMaterialSpecularModel_Phong:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UsePhongSpecularModel);break;
	case IEnum::EMaterialSpecularModel_BlinnPhong:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseBlinnPhongSpecularModel);break;
	case IEnum::EMaterialSpecularModel_UE4:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseUE4SpecularModel);break;
	case IEnum::EMaterialSpecularModel_CookTorrance:ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseCookTorranceSpecularModel);break;
	}
	if(sub_entity_interface->isAlphaTestEnable())
	{
		ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseAlphaTest);
	}
	if(sub_entity_interface->getGeometry()->getVertexBuffer()->getTextureCoords())
	{
		if(sub_entity_interface->getDiffuseTexture()&&sub_entity_interface->getDiffuseTexture()->getTexture())
		{
			ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseDiffuseTexture);
		}
		if(sub_entity_interface->getNormalTexture()&&sub_entity_interface->getNormalTexture()->getTexture())
		{
			ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseNormalTexture);
		}
		if((sub_entity_interface->getSpecularModel()!=IEnum::EMaterialSpecularModel_None)&&sub_entity_interface->getSpecularTexture()&&sub_entity_interface->getSpecularTexture()->getTexture())
		{
			ps_gen.addFlag(CForwardPixelShaderCodeGenerator::EFlag_UseSpecularTexture);
		}
	}
	auto macros=vs_gen.generateMacro();
	mPixelShader=CSystemImp::getSingleton().getPixelShader(ps_gen.generateCode(&macros));
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardPass::_updateTextures()
{
	const ISubEntityImp * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
	mVSTextures.clear();
	mPSTextures.clear();
	if(0xffffffff!=getVertexShader()->getSlot("gDiffuseTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getDiffuseTexture()->getTexture())));
	}
	if(0xffffffff!=getVertexShader()->getSlot("gNormalTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getNormalTexture()->getTexture())));
	}
	if(0xffffffff!=getPixelShader()->getSlot("gDiffuseTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getDiffuseTexture()->getTexture())));
	}
	if(0xffffffff!=getPixelShader()->getSlot("gNormalTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getNormalTexture()->getTexture())));
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
