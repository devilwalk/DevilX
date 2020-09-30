#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::ISwapChainImp(ICommandQueueImp* queue)
	:mQueue(queue)
{
}

NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::~ISwapChainImp()
{
}

ICommandQueue* NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::getCommandQueue() const
{
	return mQueue;
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::getBackBufferCount() const
{
	return static_cast<UInt32>(mBackBuffers.size());
}

IImage* NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::getBackBuffer(UInt32 index) const
{
	return mBackBuffers[index];
}

void NSDevilX::NSCore::NSGraphicsDriver::ISwapChainImp::swapBuffers()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::ISwapChainImp(ICommandQueueImp* queue,IDXGISwapChain* v)
	:NSGraphicsDriver::ISwapChainImp(queue)
	,mInternal(v)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::~ISwapChainImp()
{
}

void NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::swapBuffers()
{
	mInternal->Present(0,0);
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::ISwapChainImp::ISwapChainImp(ICommandQueueImp* queue,IDXGISwapChain* v)
	:NSD3D::ISwapChainImp(queue,v)
	,mCurrentBufferIndex(-1)
{
	DXGI_SWAP_CHAIN_DESC desc={};
	mInternal->GetDesc(&desc);
	mBackBuffers.resize(desc.BufferCount);
	for(UINT i=0;i<desc.BufferCount;++i)
	{
		ID3D12Resource* resource=nullptr;
		mInternal->GetBuffer(i,__uuidof(resource),reinterpret_cast<VoidPtr*>(&resource));
		mBackBuffers[i]=DEVILX_NEW IImageImp(static_cast<IDeviceImp*>(queue->getDevice()),resource);
	}
	CComPtr<IDXGISwapChain3> swapchain;
	mInternal->QueryInterface(&swapchain);
	mCurrentBufferIndex=swapchain->GetCurrentBackBufferIndex();
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::ISwapChainImp::~ISwapChainImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::ISwapChainImp::ISwapChainImp(ICommandQueueImp* queue,IDXGISwapChain* v)
	:NSD3D::ISwapChainImp(queue,v)
	,mInternal(v)
{
	DXGI_SWAP_CHAIN_DESC desc={};
	mInternal->GetDesc(&desc);
	mBackBuffers.resize(desc.BufferCount);
	for(UINT i=0;i<desc.BufferCount;++i)
	{
		ID3D11Texture2D* resource=nullptr;
		mInternal->GetBuffer(i,__uuidof(resource),reinterpret_cast<VoidPtr*>(&resource));
		mBackBuffers[i]=DEVILX_NEW IImageImp(static_cast<IDeviceImp*>(queue->getDevice()),resource);
	}
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::ISwapChainImp::~ISwapChainImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::ISwapChainImp(ICommandQueueImp* queue,const VkSwapchainCreateInfoKHR& info)
	:NSGraphicsDriver::ISwapChainImp(queue)
	,mInternal(VK_NULL_HANDLE)
	,mSurface(info.surface)
	,mPresentImageIndex(-1)
	,mFence(VK_NULL_HANDLE)
	,mSemaphore(VK_NULL_HANDLE)
{
	VkFenceCreateInfo fence_create_info={};
	fence_create_info.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	if(VK_SUCCESS!=vkCreateFence(static_cast<IDeviceImp*>(queue->getDevice())->getInternal(),&fence_create_info,nullptr,&mFence))
		return;
	VkSemaphoreCreateInfo semaphore_create_info={};
	semaphore_create_info.sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	if(VK_SUCCESS!=vkCreateSemaphore(static_cast<IDeviceImp*>(queue->getDevice())->getInternal(),&semaphore_create_info,nullptr,&mSemaphore))
		return;
	if(VK_SUCCESS!=vkCreateSwapchainKHR(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),&info,nullptr,&mInternal))
		return;
	uint32_t count=0;
	if(VK_SUCCESS!=vkGetSwapchainImagesKHR(static_cast<IDeviceImp*>(queue->getDevice())->getInternal(),mInternal,&count,nullptr))
		return;
	TVector<VkImage> images(count);
	vkGetSwapchainImagesKHR(static_cast<IDeviceImp*>(queue->getDevice())->getInternal(),mInternal,&count,&images[0]);
	mBackBuffers.reserve(count);
	for(auto image:images)
	{
		mBackBuffers.push_back(DEVILX_NEW IImageImp(static_cast<IDeviceImp*>(queue->getDevice()),image));
	}
	mAcquireNextImageInfo.sType=VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
	mAcquireNextImageInfo.deviceMask=0;
	for(UInt32 i=0;i<queue->getDevice()->getPhysicalDeviceGroup()->getDeviceCount();++i)
	{
		mAcquireNextImageInfo.deviceMask|=1<<i;
	}
	mAcquireNextImageInfo.fence=VK_NULL_HANDLE;
	mAcquireNextImageInfo.swapchain=mInternal;
	mAcquireNextImageInfo.timeout=-1;
	mAcquireNextImageInfo.semaphore=mSemaphore;
	mAcquireNextImageInfo.pNext=nullptr;
	if(VK_SUCCESS!=vkAcquireNextImage2KHR(static_cast<IDeviceImp*>(queue->getDevice())->getInternal(),&mAcquireNextImageInfo,&mPresentImageIndex))
		return;
	mPresentInfo.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	mPresentInfo.pNext=nullptr;
	mPresentInfo.pSwapchains=&mInternal;
	mPresentInfo.swapchainCount=1;
	mPresentInfo.waitSemaphoreCount=1;
	mPresentInfo.pWaitSemaphores=&mSemaphore;
	mPresentInfo.pResults=nullptr;
	mPresentInfo.pImageIndices=&mPresentImageIndex;

	VkImageMemoryBarrier barrier={};
	barrier.sType=VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout=VK_IMAGE_LAYOUT_UNDEFINED;
	barrier.newLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	barrier.srcQueueFamilyIndex=queue->getFamilyIndex();
	barrier.dstQueueFamilyIndex=queue->getFamilyIndex();
	for(auto image:images)
	{
		barrier.image=image;
	}
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::~ISwapChainImp()
{
	vkDestroySemaphore(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),mSemaphore,nullptr);
	vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mQueue->getDevice()->getPhysicalDeviceGroup()->getInstance())->getInternal(),mSurface,nullptr);
	vkDestroySwapchainKHR(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),mInternal,nullptr);
}

void NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ISwapChainImp::swapBuffers()
{
	vkQueuePresentKHR(static_cast<ICommandQueueImp*>(mQueue)->getInternal(),&mPresentInfo);
	vkAcquireNextImage2KHR(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),&mAcquireNextImageInfo,&mPresentImageIndex);
}
