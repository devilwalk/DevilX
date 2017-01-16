#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CPass::CPass(CTechnique * technique)
	:mTechnique(technique)
	,mForwardType(CEnum::EForwardPassType_Count)
	,mProgram(nullptr)
	,mVertexArrayObject(0)
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

NSDevilX::NSRenderSystem::NSGL4::CPass::CPass(CEnum::EForwardPassType type,CTechnique * technique)
	:mTechnique(technique)
	,mForwardType(type)
	,mProgram(nullptr)
	,mVertexArrayObject(0)
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

NSDevilX::NSRenderSystem::NSGL4::CPass::~CPass()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::onMessage(IMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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

Void NSDevilX::NSRenderSystem::NSGL4::CPass::onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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

Void NSDevilX::NSRenderSystem::NSGL4::CPass::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryImp::EMessage_EndDiffuseEnableChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITextureUnitStateImp::EMessage_EndTextureChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_updateShader()
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
		auto vertex_shader=vs_gen.generate();
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
		auto pixel_shader=ps_gen.generate(&macros);
		DEVILX_DELETE(mProgram);
		mProgram=DEVILX_NEW CProgram(vertex_shader,pixel_shader);
	}
	break;
	}
	_updateTextures();
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_updateTextures()
{
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
	mVSTextures.clear();
	mPSTextures.clear();
	if(0xffffffff!=getProgram()->getSlot("gDiffuseTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getProgram()->getSlot("gNormalTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Normal)->getTexture())));
	}
	if(0xffffffff!=getProgram()->getSlot("gDiffuseTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getProgram()->getSlot("gNormalTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::ETextureUnitStateType_Normal)->getTexture())));
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_updateRasterizerState()
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_updateBlendState()
{
	mStateFunctions[glEnable].remove(GL_BLEND);
	mStateFunctions.erase(glBlendFunci);
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		if(mat_imp->getTransparentEnable())
		{
			mStateFunctions[glEnable].push_back(GL_BLEND);
			mStateFunctions[glBlendFunci].push_back(0);
			mStateFunctions[glBlendFunci].push_back(GL_SRC_ALPHA);
			mStateFunctions[glBlendFunci].push_back(GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			switch(getForwardType())
			{
			case CEnum::EForwardPassType_Ambient:
				break;
			default:
				mStateFunctions[glEnable].push_back(GL_BLEND);
				mStateFunctions[glBlendFunci].push_back(0);
				mStateFunctions[glBlendFunci].push_back(GL_ONE);
				mStateFunctions[glBlendFunci].push_back(GL_ONE);
			}
		}
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_updateDepthStencilState()
{
	mStateFunctions.erase(glDepthMask);
	mStateFunctions.erase(glDepthFunc);
	const IMaterialImp * const mat_imp=getTechnique()->getMaterial()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		if(mat_imp->getTransparentEnable())
		{
			mStateFunctions[glDepthMask].push_back(false);
			mStateFunctions[glDepthFunc].push_back(GL_LEQUAL);
		}
		else
		{
			switch(getForwardType())
			{
			case CEnum::EForwardPassType_Ambient:
				mStateFunctions[glDepthFunc].push_back(GL_LEQUAL);
				break;
			default:
				mStateFunctions[glDepthFunc].push_back(GL_EQUAL);
				mStateFunctions[glDepthMask].push_back(false);
			}
		}
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_updateVertexArrayObject()
{
	if(mVertexArrayObject)
		glDeleteVertexArrays(1,&mVertexArrayObject);
	glGenVertexArrays(1,&mVertexArrayObject);
	for(int i=0;i<CEnum::EVertexBufferType_Count;++i)
	{
		const auto vb_type=mProgram->getInputSlot(i);
		if(static_cast<UInt32>(-1)!=vb_type)
		{
			glVertexArrayVertexBuffer(mVertexArrayObject,i,getTechnique()->getMaterial()->getRenderable()->getGeometry()->getVertexBuffer()->getBuffers()[vb_type],0,CUtility::getStride(vb_type));
			glVertexArrayAttribBinding(mVertexArrayObject,i,i);
			glVertexArrayAttribFormat(mVertexArrayObject,i,CUtility::getComponmentCount(vb_type),CUtility::getFormat(vb_type),false,0);
			glEnableVertexArrayAttrib(mVertexArrayObject,i);
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_registerToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())->addListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CPass::_unregisterToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getRenderable()->getInterfaceImp()->getGeometry())->removeListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}
