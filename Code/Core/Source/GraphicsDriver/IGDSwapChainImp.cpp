#include "../Precompiler.h"
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

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::ISwapChainImp::ISwapChainImp(IQueueImp* queue,HWND wnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullScreenDesc)
	:NSGraphicsDriver::ISwapChainImp(queue)
{
	static_cast<NSD3D::IInstanceImp*>(queue->getDevice()->getPhysicalDeviceGroup()->getInstance())->getInternal2()->CreateSwapChainForHwnd(queue->getInternal(),wnd,&desc,fullScreenDesc,nullptr,&mInternal);
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::ISwapChainImp::~ISwapChainImp()
{
}

void NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::ISwapChainImp::swapBuffers()
{
	mInternal->Present(0,0);
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::ISwapChainImp(IQueueImp* queue,const VkSwapchainCreateInfoKHR& info)
	:NSGraphicsDriver::ISwapChainImp(queue)
	,mInternal(VK_NULL_HANDLE)
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
	vkDestroySwapchainKHR(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),mInternal,nullptr);
}

void NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::swapBuffers()
{
	vkQueuePresentKHR(static_cast<IQueueImp*>(mQueue)->getInternal(),&mPresentInfo);
}
