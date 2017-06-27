#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CClearViewportProgram::CClearViewportProgram()
	:mProgram(nullptr)
{
	String code_key="ClearViewport_VertexShader";
	auto vertex_shader=CSystemImp::getSingleton().getShaderManager()->getShader(code_key);
	if(0==vertex_shader)
	{
		vertex_shader=CSystemImp::getSingleton().getShaderManager()->registerVertexShader(code_key,ISystemImp::getSingleton().getDefinitionShader()->ClearViewportVertex_glsl,TVector<std::pair<String,String> >());
	}
	code_key="ClearViewport_PixelShader";
	auto pixel_shader=CSystemImp::getSingleton().getShaderManager()->getShader(code_key);
	if(0==pixel_shader)
	{
		pixel_shader=CSystemImp::getSingleton().getShaderManager()->registerPixelShader(code_key,ISystemImp::getSingleton().getDefinitionShader()->ClearViewportPixel_glsl,TVector<std::pair<String,String> >());
	}
	mProgram=DEVILX_NEW CProgram(vertex_shader,pixel_shader);
}

NSDevilX::NSRenderSystem::NSGLES3::CClearViewportProgram::~CClearViewportProgram()
{
	DEVILX_DELETE(mProgram);
}
