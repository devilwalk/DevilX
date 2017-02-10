#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderTargetImp::CRenderTargetImp(ID3D11RenderTargetView * rt)
	:mDepthStencil(nullptr)
{
	mDepthStencil=CSystemImp::getSingleton().getFreeDepthStencil();
	setInternal(DEVILX_NEW CRenderTarget());
	getInternal()->setRTView(0,rt);
	getInternal()->setDSView(mDepthStencil->getInternal());
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderTargetImp::~CRenderTargetImp()
{
	DEVILX_DELETE(getInternal());
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTargetImp::prepare()
{
	for(auto const & viewport_pairs:mViewports)
	{
		auto viewport=viewport_pairs.second;
		viewport->prepare();
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTargetImp::render()
{
	for(auto const & viewport_pairs:mViewports)
	{
		auto viewport=viewport_pairs.second;
		viewport->render();
	}
}