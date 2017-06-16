#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CRenderTargetImp::CRenderTargetImp(GLuint rt)
{
	setInternal(DEVILX_NEW CRenderTarget());
}

NSDevilX::NSRenderSystem::NSGL4::CRenderTargetImp::~CRenderTargetImp()
{
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