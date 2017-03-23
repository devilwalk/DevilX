#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CWindowImp::CWindowImp(IWindowImp * interfaceImp)
	:TInterfaceObject<IWindowImp>(interfaceImp)
	,CRenderTargetImp(nullptr)
	,mSwapChain(nullptr)
{
	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferCount=2;
	desc.BufferDesc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Height=getInterfaceImp()->getWindow()->getSize().y;
	desc.BufferDesc.RefreshRate.Denominator=1;
	desc.BufferDesc.RefreshRate.Numerator=60;
	desc.BufferDesc.Scaling=DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering=DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Width=getInterfaceImp()->getWindow()->getSize().x;
	desc.BufferUsage=DXGI_USAGE_BACK_BUFFER|DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags=0;
	desc.OutputWindow=reinterpret_cast<decltype(desc.OutputWindow)>(getInterfaceImp()->getWindow()->getHandle());
	desc.SampleDesc.Count=1;
	desc.SampleDesc.Quality=0;
	desc.SwapEffect=DXGI_SWAP_EFFECT_DISCARD;
	desc.Windowed=TRUE;
	CSystemImp::getSingleton().getDXGIFactory()->CreateSwapChain(CSystemImp::getSingleton().getDevice(),&desc,&mSwapChain);
	getSwapChain()->GetBuffer(0,__uuidof(ID3D11Texture2D),reinterpret_cast<VoidPtr*>(&mRenderTargetResource));
	CComPtr<ID3D11RenderTargetView> temp_internal;
	CSystemImp::getSingleton().getDevice()->CreateRenderTargetView(mRenderTargetResource,nullptr,&temp_internal);
	getInternal()->setRTView(0,temp_internal);
	mDepthStencil->reserve(desc.BufferDesc.Width,desc.BufferDesc.Height);
	getInternal()->setDSView(mDepthStencil->getInternal());
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IWindowImp>*>(this),IWindowImp::EMessage_EndViewportCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IWindowImp>*>(this),IWindowImp::EMessage_BeginViewportDestroy);
}

NSDevilX::NSRenderSystem::NSD3D11::CWindowImp::~CWindowImp()
{
	if(mRenderTargetResource)
		mRenderTargetResource->Release();
	if(mSwapChain)
		mSwapChain->Release();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CWindowImp::prepare()
{
	DXGI_SWAP_CHAIN_DESC desc;
	getSwapChain()->GetDesc(&desc);
	if(getInterfaceImp()->getWindow()->getSize()!=CUInt2(desc.BufferDesc.Width,desc.BufferDesc.Height))
	{
		_resize();
	}
	CRenderTargetImp::prepare();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CWindowImp::render()
{
	CRenderTargetImp::render();
	getSwapChain()->Present(0,0);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CWindowImp::_resize()
{
	notify(EMessage_BeginResize);
	getInternal()->setRTView(0,nullptr);
	mRenderTargetResource->Release();
	CSystemImp::getSingleton().getImmediateContext()->ClearState();
	getSwapChain()->ResizeBuffers(2,0,0,DXGI_FORMAT_R8G8B8A8_UNORM,0);
	getSwapChain()->GetBuffer(0,__uuidof(ID3D11Texture2D),reinterpret_cast<VoidPtr*>(&mRenderTargetResource));
	CComPtr<ID3D11RenderTargetView> rt;
	CSystemImp::getSingleton().getDevice()->CreateRenderTargetView(mRenderTargetResource,nullptr,&rt);
	getInternal()->setRTView(0,rt);
	DXGI_SWAP_CHAIN_DESC desc;
	getSwapChain()->GetDesc(&desc);
	mDepthStencil->reserve(desc.BufferDesc.Width,desc.BufferDesc.Height);
	getInternal()->setDSView(mDepthStencil->getInternal());
	getInternal()->needUpdate();
	notify(EMessage_EndResize);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CWindowImp::onMessage(IWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IWindowImp::EMessage_EndViewportCreate:
	{
		CViewportImp * vp=DEVILX_NEW CViewportImp(static_cast<IViewportImp*>(data));
		mViewports[static_cast<IViewportImp*>(data)]=vp;
	}
	break;
	case IWindowImp::EMessage_BeginViewportDestroy:
		mViewports.destroy(static_cast<IViewportImp*>(data));
		break;
	}
}
