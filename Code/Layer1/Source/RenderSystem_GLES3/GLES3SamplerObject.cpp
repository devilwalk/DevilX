#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CSamplerObject::CSamplerObject(const SSamplerDescription & desc)
	:mInternal(0)
{
	glGenSamplers(1,&mInternal);
	CUtility::checkGLError();
	for(auto state:desc.mStates)
	{
		glSamplerParameteri(getInternal(),state.first,state.second);
		CUtility::checkGLError();
	}
	glSamplerParameterfv(getInternal(),GL_TEXTURE_BORDER_COLOR,reinterpret_cast<const GLfloat*>(static_cast<const CFloat4*>(&desc.mBorderColor)));
	CUtility::checkGLError();
}

NSDevilX::NSRenderSystem::NSGLES3::CSamplerObject::~CSamplerObject()
{
	if(getInternal())
	{
		glDeleteSamplers(1,&mInternal);
		CUtility::checkGLError();
	}
}
