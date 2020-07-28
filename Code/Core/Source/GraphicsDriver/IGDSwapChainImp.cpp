#include "../Precompiler.h"
#include "..\..\Include\GraphicsDriver\IGDSwapChainImp.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::ISwapChainImp(IQueueImp* queue)
	:mQueue(queue)
{
}

NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::~ISwapChainImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::ISwapChainImp(NSD3D12::IQueueImp* queue,HWND wnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullScreenDesc)
	:NSGraphicsDriver::ISwapChainImp(queue)
{
	IDXGISwapChain1* sc=nullptr;
	static_cast<NSD3D::IInstanceImp*>(queue->getDevice()->getPhysicalDeviceGroup()->getInstance())->getInternal2()->CreateSwapChainForHwnd(queue->getInternal(),wnd,&desc,fullScreenDesc,nullptr,&sc);
	mInternal=sc;
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::ISwapChainImp(NSD3D11::IDeviceImp* dev,HWND wnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullScreenDesc)
	:NSGraphicsDriver::ISwapChainImp(dev)
{
	IDXGISwapChain1* sc=nullptr;
	static_cast<NSD3D::IInstanceImp*>(dev->getPhysicalDeviceGroup()->getInstance())->getInternal2()->CreateSwapChainForHwnd(dev->getInternal(),wnd,&desc,fullScreenDesc,nullptr,&sc);
	mInternal=sc;
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::ISwapChainImp(NSD3D11::IDeviceImp* dev,DXGI_SWAP_CHAIN_DESC& desc)
	:NSGraphicsDriver::ISwapChainImp(dev)
{
	static_cast<NSD3D::IInstanceImp*>(dev->getPhysicalDeviceGroup()->getInstance())->getInternal()->CreateSwapChain(dev->getInternal(),&desc,&mInternal);
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::~ISwapChainImp()
{
}

void NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::swapBuffers()
{
	mInternal->Present(0,0);
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::ISwapChainImp(IQueueImp* queue,const VkSwapchainCreateInfoKHR& info)
	:NSGraphicsDriver::ISwapChainImp(queue)
	,mInternal(VK_NULL_HANDLE)
	,mSurface(info.surface)
{
	vkCreateSwapchainKHR(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),&info,nullptr,&mInternal);
	mPresentInfo.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	mPresentInfo.pNext=nullptr;
	mPresentInfo.pSwapchains=&mInternal;
	mPresentInfo.swapchainCount=1;
	mPresentInfo.waitSemaphoreCount=0;
	mPresentInfo.pWaitSemaphores=nullptr;
	mPresentInfo.pResults=nullptr;
	mPresentInfo.pImageIndices=nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::~ISwapChainImp()
{
	vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mQueue->getDevice()->getPhysicalDeviceGroup()->getInstance())->getInternal(),mSurface,nullptr);
	vkDestroySwapchainKHR(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),mInternal,nullptr);
}

void NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::swapBuffers()
{
	vkQueuePresentKHR(static_cast<IQueueImp*>(mQueue)->getInternal(),&mPresentInfo);
}
