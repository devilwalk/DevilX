#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderCommandListImp::CRenderCommandListImp(ID3D11DeviceContext * context)
	:mContext(context)
	,mCommandList(nullptr)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderCommandListImp::~CRenderCommandListImp()
{
	DEVILX_COM_SAFE_RELEASE(mCommandList);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderCommandListImp::clearRenderTarget(CRenderTarget * renderTarget)
{
	if(renderTarget->getClearRects().empty())
	{
		if(dynamic_cast<CColourSurfaceImp*>(renderTarget))
			mContext->ClearRenderTargetView(static_cast<CColourSurfaceImp*>(renderTarget)->getInternal(),&static_cast<CColourSurfaceImp*>(renderTarget)->getClearColour()[0]);
		else
			mContext->ClearDepthStencilView(static_cast<CDepthStencilSurfaceImp*>(renderTarget)->getInternal()
				,(static_cast<CDepthStencilSurfaceImp*>(renderTarget)->isClearDepth()?D3D11_CLEAR_DEPTH:0)|(static_cast<CDepthStencilSurfaceImp*>(renderTarget)->isClearStencil()?D3D11_CLEAR_STENCIL:0)
			,static_cast<CDepthStencilSurfaceImp*>(renderTarget)->getClearDepth(),static_cast<CDepthStencilSurfaceImp*>(renderTarget)->getClearStencil());
	}
	else
	{

	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderCommandListImp::renderOperation(const CRenderOperation & op)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderCommandListImp::execute(Bool sync=False)
{
	mContext->FinishCommandList(TRUE,&mCommandList);
	CSystemImp::getSingleton().getImmediateContext()->ExecuteCommandList(mCommandList,TRUE);
	DEVILX_COM_SAFE_RELEASE(mCommandList);
}
