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
	auto pixel_shader=CSystemImp::getSingleton().getShaderManager()->getShader(code_key);
	if(0==pixel_shader)
	{
		pixel_shader=CSystemImp::getSingleton().getShaderManager()->registerPixelShader(code_key,CSystemImp::getSingleton().getDefinitionShader()->OverlayShaderPixel,TVector<std::pair<String,String> >());
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
	mStateFunctions[glBlendFunc][0].push_back(GL_SRC_ALPHA);
	mStateFunctions[glBlendFunc][0].push_back(GL_ONE_MINUS_SRC_ALPHA);
	mStateFunctions[glBlendFunc][1].push_back(GL_ONE);
	mStateFunctions[glBlendFunc][1].push_back(GL_ZERO);
}

Void NSDevilX::NSRenderSystem::NSGL4::COverlayMaterial::_updateDepthStencilState()
{
	mStateFunctions[glDepthMask][0].push_back(false);
	mStateFunctions[glDepthMask][1].push_back(true);
	mStateFunctions[glDepthFunc][0].push_back(GL_ALWAYS);
	mStateFunctions[glDepthFunc][1].push_back(GL_LEQUAL);
}