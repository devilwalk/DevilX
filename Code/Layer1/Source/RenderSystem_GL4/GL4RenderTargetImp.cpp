#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CRenderTargetImp::CRenderTargetImp(GLuint rt)
	:mRenderTargetResource(0)
	,mDepthStencil(nullptr)
{
	mDepthStencil=CSystemImp::getSingleton().getFreeDepthStencil();
	setInternal(DEVILX_NEW CRenderTarget());
	getInternal()->setRT(0,rt);
	getInternal()->setDS(mDepthStencil->getInternal());
}

NSDevilX::NSRenderSystem::NSGL4::CRenderTargetImp::~CRenderTargetImp()
{
	if(mRenderTargetResource)
		glDeleteTextures(1,&mRenderTargetResource);
	DEVILX_DELETE(getInternal());
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTargetImp::prepare()
{
	for(auto const & viewport_pairs:mViewports)
	{
		auto viewport=viewport_pairs.second;
		viewport->prepare();
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTargetImp::render()
{
	for(auto const & viewport_pairs:mViewports)
	{
		auto viewport=viewport_pairs.second;
		viewport->render();
	}
}