#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::CRenderTarget()
	:CConstantBufferContainer("cbRenderTarget")
	,mFrameBuffer(0)
	,mDepthStencil(0)
{
	memset(mRenderTargets,0,sizeof(mRenderTargets));
	glGenFramebuffers(1,&mFrameBuffer);
}

NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::~CRenderTarget()
{
	for(auto i=0;i<8;++i)
		setRT(i,0);
	setDS(0);
	glDeleteFramebuffers(1,&mFrameBuffer);
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::getSize(GLsizei & width,GLsizei & height)
{
	for(auto i=0;i<8;++i)
	{
		if(mRenderTargets[i])
		{
			glGetTextureLevelParameteriv(mRenderTargets[i],0,GL_TEXTURE_WIDTH,&width);
			glGetTextureLevelParameteriv(mRenderTargets[i],0,GL_TEXTURE_HEIGHT,&height);
			break;
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::setRT(UInt32 index,GLuint texture)
{
	mRenderTargets[index]=texture;
	glNamedFramebufferTexture(getFrameBuffer(),GL_COLOR_ATTACHMENT0+index,texture,0);
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::setDS(GLuint texture)
{
	mDepthStencil=texture;
	glNamedFramebufferTexture(getFrameBuffer(),GL_DEPTH_STENCIL_ATTACHMENT,texture,0);
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::clear(UInt32 index,const CColour & colour)
{
	if(0==mRenderTargets[index])
		return;
	GLint fmt=0;
	glGetTextureLevelParameteriv(mRenderTargets[index],0,GL_TEXTURE_INTERNAL_FORMAT,&fmt);

	switch(fmt)
	{
	case GL_RGBA16F:
	case GL_RGBA32F:
	case GL_RGBA8:
	{
		GLfloat clear_value[]={colour.r(),colour.g(),colour.b(),colour.a()};
		glClearNamedFramebufferfv(getFrameBuffer(),GL_COLOR,GL_DRAW_BUFFER0+index,clear_value);
	}
	break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::clear(Float depth,Int32 stencil)
{
	if((depth>=0)&&(stencil>=0))
		glClearNamedFramebufferfi(getFrameBuffer(),GL_DEPTH_STENCIL,0,depth,stencil);
	else if(depth>=0)
	{
		glClearNamedFramebufferfv(getFrameBuffer(),GL_DEPTH,0,&depth);
	}
	else if(stencil>=0)
	{
		glClearNamedFramebufferiv(getFrameBuffer(),GL_STENCIL,0,&stencil);
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::setup()
{
	glBindFramebuffer(GL_FRAMEBUFFER,getFrameBuffer());
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTarget::_updateConstantBuffer(Byte * buffer)
{
	GLsizei width=0;
	GLsizei height=0;
	getSize(width,height);
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gRenderTargetSizeInPixel").mOffsetInBytes;
	memcpy(&buffer[offset],&CFloat2(static_cast<Float>(width),static_cast<Float>(height)),sizeof(CFloat2));
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseRenderTargetSizeInPixel").mOffsetInBytes;
	memcpy(&buffer[offset],&CFloat2(1.0f/width,1.0f/height),sizeof(CFloat2));
}
