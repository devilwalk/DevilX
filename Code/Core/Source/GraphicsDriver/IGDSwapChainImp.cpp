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

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::ISwapChainImp::ISwapChainImp(IQueueImp* queue,IDXGISwapChain* v)
	:NSGraphicsDriver::ISwapChainImp(queue)
	,mInternal(v)
	,mCurrentBufferIndex12(-1)
{
	DXGI_SWAP_CHAIN_DESC desc={};
	mInternal->GetDesc(&desc);
	switch(queue->getDevice()->getPhysicalDeviceGroup()->getInstance()->getMinorType())
	{
	case IEnum::EInstanceMinorType_D3D_12_1:
	case IEnum::EInstanceMinorType_D3D_12_0:
		mBackBuffers12.resize(desc.BufferCount);
		for(UINT i=0;i<desc.BufferCount;++i)
		{
			mInternal->GetBuffer(i,__uuidof(mBackBuffers12[i]),reinterpret_cast<VoidPtr*>(&mBackBuffers12[i]));
		}
		{
			CComPtr<IDXGISwapChain3> swapchain;
			mInternal->QueryInterface(&swapchain);
			mCurrentBufferIndex12=swapchain->GetCurrentBackBufferIndex();
		}
		break;
	case IEnum::EInstanceMinorType_D3D_11_1:
	case IEnum::EInstanceMinorType_D3D_11_0:
		mBackBuffers11.resize(desc.BufferCount);
		for(UINT i=0;i<desc.BufferCount;++i)
		{
			mInternal->GetBuffer(i,__uuidof(mBackBuffers11[i]),reinterpret_cast<VoidPtr*>(&mBackBuffers11[i]));
		}
		break;
	}
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
	mImages.resize(count);
	vkGetSwapchainImagesKHR(static_cast<IDeviceImp*>(queue->getDevice())->getInternal(),mInternal,&count,&mImages[0]);
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
	for(auto image:mImages)
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
	vkQueuePresentKHR(static_cast<IQueueImp*>(mQueue)->getInternal(),&mPresentInfo);
	vkAcquireNextImage2KHR(static_cast<IDeviceImp*>(mQueue->getDevice())->getInternal(),&mAcquireNextImageInfo,&mPresentImageIndex);
}
