#include "../Precompiler.h"
#include "..\..\Include\GraphicsDriver\IGDQueueImp.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IQueueImp::IQueueImp(IDeviceImp* dev)
	:mDevice(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IQueueImp::~IQueueImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::IQueueImp(IDeviceImp* dev,ID3D12CommandQueue* queue)
	:NSGraphicsDriver::IQueueImp(dev)
	,mInternal(queue)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::~IQueueImp()
{
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::createSwapChain(DXGI_SWAP_CHAIN_DESC& desc)
{
	DXGI_SWAP_CHAIN_DESC1 desc1={};
	desc1.AlphaMode=DXGI_ALPHA_MODE_IGNORE;
	desc1.BufferCount=desc.BufferCount;
	desc1.BufferUsage=desc.BufferUsage;
	desc1.Flags=desc.Flags;
	desc1.Format=desc.BufferDesc.Format;
	desc1.Height=desc.BufferDesc.Height;
	desc1.SampleDesc=desc.SampleDesc;
	switch(desc.BufferDesc.Scaling)
	{
	case DXGI_MODE_SCALING_UNSPECIFIED:
		desc1.Scaling=DXGI_SCALING_NONE;
		break;
	case DXGI_MODE_SCALING_CENTERED:
		desc1.Scaling=DXGI_SCALING_ASPECT_RATIO_STRETCH;
		break;
	case DXGI_MODE_SCALING_STRETCHED:
		desc1.Scaling=DXGI_SCALING_STRETCH;
		break;
	}
	desc1.Stereo=FALSE;
	desc1.SwapEffect=desc.SwapEffect;
	desc1.Width=desc.BufferDesc.Width;
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC full_screen_desc={};
	full_screen_desc.RefreshRate=desc.BufferDesc.RefreshRate;
	full_screen_desc.Scaling=desc.BufferDesc.Scaling;
	full_screen_desc.ScanlineOrdering=desc.BufferDesc.ScanlineOrdering;
	full_screen_desc.Windowed=desc.Windowed;
	return createSwapChain(desc.OutputWindow,desc1,&full_screen_desc);
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
	auto ret=DEVILX_NEW NSD3D::ISwapChainImp(this,hwnd,desc,fullscreenDesc);
	mSwapChains.push_back(ret);
	return ret;
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::IQueueImp(IDeviceImp* dev,VkQueue queue)
	:NSGraphicsDriver::IQueueImp(dev)
	,mInternal(queue)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::~IQueueImp()
{
}
