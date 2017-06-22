#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CDepthStencil::CDepthStencil()
	:mInternal(0)
	,mLocked(False)
{}

NSDevilX::NSRenderSystem::NSGLES3::CDepthStencil::~CDepthStencil()
{
	if(getInternal())
	{
		glDeleteRenderbuffers(1,&mInternal);
		CUtility::checkGLError();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CDepthStencil::reserve(UInt32 width,UInt32 height)
{
	if(getInternal())
	{
		glDeleteRenderbuffers(1,&mInternal);
		CUtility::checkGLError();
		mInternal=0;
	}
	glGenRenderbuffers(1,&mInternal);
	CUtility::checkGLError();
	glBindRenderbuffer(GL_RENDERBUFFER,getInternal());
	CUtility::checkGLError();
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	CUtility::checkGLError();
	glNamedRenderbufferStorage(getInternal(),GL_DEPTH_STENCIL,width,height);
	CUtility::checkGLError();
}
