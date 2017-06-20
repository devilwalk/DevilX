#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::COverlayMaterial::COverlayMaterial(CTexture * texture)
{
	if(texture)
		mPSTextures.push_back(texture);
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
}

NSDevilX::NSRenderSystem::NSGL4::COverlayMaterial::~COverlayMaterial()
{
	DEVILX_DELETE(mProgram);
}

Void NSDevilX::NSRenderSystem::NSGL4::COverlayMaterial::_updateShader()
{
	String code_key="Overlay_VertexShader";
	auto vertex_shader=CSystemImp::getSingleton().getShaderManager()->getShader(code_key);
	if(0==vertex_shader)
	{
		vertex_shader=CSystemImp::getSingleton().getShaderManager()->registerVertexShader(code_key,CSystemImp::getSingleton().getDefinitionShader()->OverlayShaderVertex,TVector<std::pair<String,String> >());
	}

	code_key="Overlay_PixelShader";
	if(!mPSTextures.empty())
	{
		if(static_cast<CTexture2D*>(mPSTextures[0])->getInterfaceImp()->getFormat()==IEnum::ETexture2DFormat_A8)
		{
			code_key+="/FontTexture";
		}
		else
		{
			code_key+="/DiffuseTexture";
		}
	}
	auto pixel_shader=CSystemImp::getSingleton().getShaderManager()->getShader(code_key);
	if(0==pixel_shader)
	{
		TVector<std::pair<String,String> > macros;
		std::pair<String,String> def;
		if(!mPSTextures.empty())
		{
			if(static_cast<CTexture2D*>(mPSTextures[0])->getInterfaceImp()->getFormat()==IEnum::ETexture2DFormat_A8)
			{
				def.first="USE_FONT_TEXTURE";
				def.second="1";
				macros.push_back(def);
			}
			else
			{
				def.first="USE_DIFFUSE_TEXTURE";
				def.second="1";
				macros.push_back(def);
			}
		}
		pixel_shader=CSystemImp::getSingleton().getShaderManager()->registerPixelShader(code_key,CSystemImp::getSingleton().getDefinitionShader()->OverlayShaderPixel,macros);
	}
	mProgram=DEVILX_NEW CProgram(vertex_shader,pixel_shader);
}

Void NSDevilX::NSRenderSystem::NSGL4::COverlayMaterial::_updateRasterizerState()
{
	mDisableState.push_back(GL_CULL_FACE);
	mEnabledState.push_back(GL_SCISSOR_TEST);
}

Void NSDevilX::NSRenderSystem::NSGL4::COverlayMaterial::_updateBlendState()
{
	mEnabledState.push_back(GL_BLEND);
	mStateFunctions[glBlendFunc].push_back(GL_SRC_ALPHA);
	mStateFunctions[glBlendFunc].push_back(GL_ONE_MINUS_SRC_ALPHA);
}

Void NSDevilX::NSRenderSystem::NSGL4::COverlayMaterial::_updateDepthStencilState()
{
	mStateFunctions[glDepthMask].push_back(false);
	mStateFunctions[glDepthFunc].push_back(GL_ALWAYS);
}