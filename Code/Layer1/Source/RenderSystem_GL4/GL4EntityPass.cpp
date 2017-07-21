#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CEntityPass::CEntityPass(CEntityTechnique * technique)
	:mTechnique(technique)
	,mForwardType(CEnum::EForwardPassType_Count)
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

NSDevilX::NSRenderSystem::NSGL4::CEntityPass::CEntityPass(CEnum::EForwardPassType type,CEntityTechnique * technique)
	:mTechnique(technique)
	,mForwardType(type)
	,mVertexArrayObject(0)
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

NSDevilX::NSRenderSystem::NSGL4::CEntityPass::~CEntityPass()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
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
	case ISubEntityImp::EMessage_BeginGeometryChange:
		_unregisterToIGeometryImp();
		break;
	case ISubEntityImp::EMessage_EndGeometryChange:
		_updateShader();
		_registerToIGeometryImp();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryImp::EMessage_EndDiffuseEnableChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITextureUnitStateImp::EMessage_EndTextureChange:
		_updateShader();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_updateShader()
{
	if(nullptr==getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())
		return;
	const auto * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
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
		auto vertex_shader=vs_gen.generate();
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
		auto pixel_shader=ps_gen.generate(&macros);
		DEVILX_DELETE(mProgram);
		mProgram=DEVILX_NEW CProgram(vertex_shader,pixel_shader);
	}
	break;
	}
	_updateTextures();
	_updateVertexArrayObject();
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_updateTextures()
{
	const auto * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
	mVSTextures.clear();
	mPSTextures.clear();
	if(0xffffffff!=getProgram()->getSlot("gDiffuseTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getProgram()->getSlot("gNormalTexture"))
	{
		mVSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Normal)->getTexture())));
	}
	if(0xffffffff!=getProgram()->getSlot("gDiffuseTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Diffuse)->getTexture())));
	}
	if(0xffffffff!=getProgram()->getSlot("gNormalTexture"))
	{
		mPSTextures.push_back(CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(mat_imp->getTextureUnitState(IEnum::EEntityTextureUnitStateType_Normal)->getTexture())));
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_updateRasterizerState()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_updateBlendState()
{
	mEnabledState.remove(GL_BLEND);
	mStateFunctions.erase(glBlendFunci);
	const auto * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		if(mat_imp->getTransparentEnable())
		{
			mEnabledState.push_back(GL_BLEND);
			mStateFunctions[glBlendFunci][0].push_back(0);
			mStateFunctions[glBlendFunci][0].push_back(GL_SRC_ALPHA);
			mStateFunctions[glBlendFunci][0].push_back(GL_ONE_MINUS_SRC_ALPHA);
			mStateFunctions[glBlendFunci][1].push_back(0);
			mStateFunctions[glBlendFunci][1].push_back(GL_ONE);
			mStateFunctions[glBlendFunci][1].push_back(GL_ZERO);
		}
		else
		{
			switch(getForwardType())
			{
			case CEnum::EForwardPassType_Ambient:
				break;
			default:
				mEnabledState.push_back(GL_BLEND);
				mStateFunctions[glBlendFunci][0].push_back(0);
				mStateFunctions[glBlendFunci][0].push_back(GL_ONE);
				mStateFunctions[glBlendFunci][0].push_back(GL_ONE);
				mStateFunctions[glBlendFunci][1].push_back(0);
				mStateFunctions[glBlendFunci][1].push_back(GL_ONE);
				mStateFunctions[glBlendFunci][1].push_back(GL_ZERO);
			}
		}
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_updateDepthStencilState()
{
	mStateFunctions.erase(glDepthMask);
	mStateFunctions.erase(glDepthFunc);
	const auto * const mat_imp=getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp();
	switch(getTechnique()->getType())
	{
	case CEnum::ETechniqueType_Forward:
		if(mat_imp->getTransparentEnable())
		{
			mStateFunctions[glDepthMask][0].push_back(false);
			mStateFunctions[glDepthMask][1].push_back(true);
			mStateFunctions[glDepthFunc][0].push_back(GL_LEQUAL);
			mStateFunctions[glDepthFunc][1].push_back(GL_LEQUAL);
		}
		else
		{
			switch(getForwardType())
			{
			case CEnum::EForwardPassType_Ambient:
				mStateFunctions[glDepthFunc][0].push_back(GL_LEQUAL);
				mStateFunctions[glDepthFunc][1].push_back(GL_LEQUAL);
				break;
			default:
				mStateFunctions[glDepthFunc][0].push_back(GL_EQUAL);
				mStateFunctions[glDepthFunc][1].push_back(GL_EQUAL);
				mStateFunctions[glDepthMask][0].push_back(false);
				mStateFunctions[glDepthMask][0].push_back(true);
			}
		}
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_updateVertexArrayObject()
{
	if(mVertexArrayObject)
	{
		glDeleteVertexArrays(1,&mVertexArrayObject);
		CUtility::checkGLError();
	}
	glGenVertexArrays(1,&mVertexArrayObject);
	CUtility::checkGLError();
	glBindVertexArray(mVertexArrayObject);
	CUtility::checkGLError();
	for(int i=0;i<CEnum::EVertexBufferType_Count;++i)
	{
		const auto vb_type=getProgram()->getInputSlot(i);
		if(static_cast<UInt32>(-1)!=vb_type)
		{
			glBindBuffer(GL_ARRAY_BUFFER,getTechnique()->getMaterial()->getSubEntity()->getGeometry()->getVertexBuffer()->getBuffers()[vb_type]);
			CUtility::checkGLError();
			if(CEnum::EVertexBufferType_BlendIndex==vb_type)
			{
				glVertexAttribIPointer(i,CUtility::getComponmentCount(vb_type),CUtility::getFormat(vb_type),CUtility::getStride(vb_type),nullptr);
			}
			else
			{
				glVertexAttribPointer(i,CUtility::getComponmentCount(vb_type),CUtility::getFormat(vb_type),CUtility::needNormalized(vb_type),CUtility::getStride(vb_type),nullptr);
				CUtility::checkGLError();
			}
			glEnableVertexAttribArray(i);
			CUtility::checkGLError();
		}
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,getTechnique()->getMaterial()->getSubEntity()->getGeometry()->getIndexBuffer()->getBuffer());
	CUtility::checkGLError();
	glBindVertexArray(0);
	CUtility::checkGLError();
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_registerToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())->addListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityPass::_unregisterToIGeometryImp()
{
	if(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())
	{
		static_cast<IGeometryImp*>(getTechnique()->getMaterial()->getSubEntity()->getInterfaceImp()->getGeometry())->removeListener(static_cast<TMessageReceiver<IGeometryImp>*>(this),IGeometryImp::EMessage_EndDiffuseEnableChange);
	}
}
