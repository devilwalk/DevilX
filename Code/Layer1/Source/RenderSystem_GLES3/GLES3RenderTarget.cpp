#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::CRenderTarget()
	:CConstantBufferContainer("cbRenderTarget")
	,mFrameBuffer(0)
	,mDepthStencil(0)
	,mWidth(0)
	,mHeight(0)
{
	memset(mRenderTargets,0,sizeof(mRenderTargets));
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::~CRenderTarget()
{
	for(auto i=0;i<8;++i)
		setRT(i,0);
	setDS(0);
	if(0!=getFrameBuffer())
	{
		glDeleteFramebuffers(1,&mFrameBuffer);
		CUtility::checkGLError();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::setRT(UInt32 index,GLuint texture)
{
	mRenderTargets[index]=texture;
	_updateFrameBuffer();
	if(0!=getFrameBuffer())
	{
		glBindFramebuffer(GL_FRAMEBUFFER,getFrameBuffer());
		CUtility::checkGLError();
		glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+index,texture,0);
		CUtility::checkGLError();
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		CUtility::checkGLError();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::setDS(GLuint ds)
{
	mDepthStencil=ds;
	_updateFrameBuffer();
	if(0!=getFrameBuffer())
	{
		glBindFramebuffer(GL_FRAMEBUFFER,getFrameBuffer());
		CUtility::checkGLError();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,mDepthStencil);
		CUtility::checkGLError();
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		CUtility::checkGLError();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::clear(UInt32 index,const CColour & colour)
{
	if(0==getFrameBuffer())
	{
		if(0==index)
		{
			glClearColor(colour.r(),colour.g(),colour.b(),colour.a());
			CUtility::checkGLError();
			glClear(GL_COLOR_BUFFER_BIT);
			CUtility::checkGLError();
		}
	}
	else
	{
		GLint fmt=0;
		glBindTexture(GL_TEXTURE_2D,mRenderTargets[index]);
		CUtility::checkGLError();
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT,&fmt);
		CUtility::checkGLError();
		glBindTexture(GL_TEXTURE_2D,0);
		CUtility::checkGLError();
		switch(fmt)
		{
		case GL_RGBA16F:
		case GL_RGBA32F:
		case GL_RGBA8:
		{
			GLfloat clear_value[]={colour.r(),colour.g(),colour.b(),colour.a()};
			GLint cur_frame_buffer=0;
			glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&cur_frame_buffer);
			CUtility::checkGLError();
			glBindFramebuffer(GL_FRAMEBUFFER,getFrameBuffer());
			CUtility::checkGLError();
			glClearBufferfv(GL_COLOR,index,clear_value);
			CUtility::checkGLError();
			glBindFramebuffer(GL_FRAMEBUFFER,cur_frame_buffer);
			CUtility::checkGLError();
		}
		break;
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::clear(Float depth,Int32 stencil)
{
	GLint cur_frame_buffer=0;
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING ,&cur_frame_buffer);
	CUtility::checkGLError();
	glBindFramebuffer(GL_FRAMEBUFFER,getFrameBuffer());
	CUtility::checkGLError();
	if(depth>=0)
	{
		glClearDepthf(depth);
		CUtility::checkGLError();
	}
	if(stencil>=0)
	{
		glClearStencil(stencil);
		CUtility::checkGLError();
	}
	glClear(((depth>=0)?GL_DEPTH_BUFFER_BIT:0)|((stencil>=0)?GL_STENCIL_BUFFER_BIT:0));
	CUtility::checkGLError();
	glBindFramebuffer(GL_FRAMEBUFFER,cur_frame_buffer);
	CUtility::checkGLError();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::setup()
{
	glBindFramebuffer(GL_FRAMEBUFFER,getFrameBuffer());
	CUtility::checkGLError();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::_updateFrameBuffer()
{
	Boolean is_default_fb=mDepthStencil==0;
	for(auto i=0;i<8;++i)
	{
		is_default_fb&=mRenderTargets[i]==0;
	}
	if(is_default_fb)
	{
		if(0!=getFrameBuffer())
		{
			glDeleteFramebuffers(1,&mFrameBuffer);
			CUtility::checkGLError();
			mFrameBuffer=0;
		}
	}
	else
	{
		glGenFramebuffers(1,&mFrameBuffer);
		CUtility::checkGLError();
		glBindFramebuffer(GL_FRAMEBUFFER,getFrameBuffer());
		CUtility::checkGLError();
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		CUtility::checkGLError();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTarget::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gRenderTargetSizeInPixel").mOffsetInBytes;
	memcpy(&buffer[offset],&CFloat2(static_cast<Float>(getWidth()),static_cast<Float>(getHeight())),sizeof(CFloat2));
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseRenderTargetSizeInPixel").mOffsetInBytes;
	memcpy(&buffer[offset],&CFloat2(1.0f/getWidth(),1.0f/getHeight()),sizeof(CFloat2));
}
