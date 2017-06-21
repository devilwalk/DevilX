#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CSamplerObject::CSamplerObject(const SSamplerDescription & desc)
	:mInternal(0)
{
	glCreateSamplers(1,&mInternal);
	for(auto state:desc.mStates)
		glSamplerParameteri(getInternal(),state.first,state.second);
	glSamplerParameterfv(getInternal(),GL_TEXTURE_BORDER_COLOR,reinterpret_cast<const GLfloat*>(&desc.mBorderColor));
}

NSDevilX::NSRenderSystem::NSGL4::CSamplerObject::~CSamplerObject()
{
	if(getInternal())
	{
		glDeleteSamplers(1,&mInternal);
	}
}
