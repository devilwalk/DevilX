#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CDepthStencil::CDepthStencil()
	:mInternal(0)
	,mLocked(False)
{}

NSDevilX::NSRenderSystem::NSGL4::CDepthStencil::~CDepthStencil()
{
	if(getInternal())
		glDeleteTextures(1,&mInternal);
}

Void NSDevilX::NSRenderSystem::NSGL4::CDepthStencil::reserve(UInt32 width,UInt32 height)
{
	if(getInternal())
	{
		glDeleteTextures(1,&mInternal);
		mInternal=0;
	}
	glGenTextures(1,&mInternal);
	glTextureImage2DEXT(getInternal(),GL_TEXTURE_2D,1,GL_DEPTH_STENCIL,width,height,0,GL_DEPTH_STENCIL,GL_UNSIGNED_BYTE,nullptr);
}
