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
		/*D3D11_TEXTURE2D_DESC desc;
		mTextureResource->GetDesc(&desc);
		if((desc.Width>=width)&&(desc.Height>=height))
			return;*/
		glDeleteTextures(1,&mInternal);
		mInternal=0;
	}
	glGenTextures(1,&mInternal);
	glTextureStorage2D(getInternal(),1,GL_DEPTH24_STENCIL8,width,height);
}
