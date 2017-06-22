#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CRenderTargetImp::CRenderTargetImp(GLuint rt)
{
	setInternal(DEVILX_NEW CRenderTarget());
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderTargetImp::~CRenderTargetImp()
{
	DEVILX_DELETE(getInternal());
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTargetImp::prepare()
{
	for(auto const & viewport_pairs:mViewports)
	{
		auto viewport=viewport_pairs.second;
		viewport->prepare();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTargetImp::render()
{
	for(auto const & viewport_pairs:mViewports)
	{
		auto viewport=viewport_pairs.second;
		viewport->render();
	}
}