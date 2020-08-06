#pragma once

#include "resource.h"

class CGATester
	:public NSDevilX::TSingletonEx<CGATester>
{
protected:
	NSDevilX::NSCore::NSGraphicsDriver::IDevice* mDevice;
	NSDevilX::NSCore::NSGraphicsDriver::IQueue* m3DQueue;
	NSDevilX::NSCore::NSGraphicsDriver::IMemoryAllocator* mMemoryAllocator;
	NSDevilX::NSCore::NSGraphicsDriver::ISwapChain* mSwapChain;
public:
	CGATester()
		:mDevice(nullptr)
		,m3DQueue(nullptr)
		,mMemoryAllocator(nullptr)
		,mSwapChain(nullptr)
	{
	}
	~CGATester()
	{
	}

	NSDevilX::Void initialize(HWND wnd)
	{
		auto instance_major_type=NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMajorType_Vulkan;
		auto instance_minor_type=NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMinorType_D3D_12_1;
		auto inst=NSDevilX::NSCore::getSystem()->getGraphicsDriverSystem()->createInstance(instance_major_type,instance_minor_type);
		NSDevilX::TVector<NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroup*> physics_device_groups;
		physics_device_groups.resize(inst->enumPhysicalDeviceGroups(nullptr));
		inst->enumPhysicalDeviceGroups(&physics_device_groups[0]);
		mDevice=inst->createDevice(physics_device_groups[0]);
		mMemoryAllocator=mDevice->createMemoryAllocator(0);
		m3DQueue=mDevice->getQueue(NSDevilX::NSCore::NSGraphicsDriver::IEnum::EQueue_3D,0);
		if(0)
		{
			DXGI_SWAP_CHAIN_DESC1 desc={};
			desc.BufferCount=2;
			desc.BufferUsage=DXGI_USAGE_BACK_BUFFER;
			desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
			desc.SampleDesc.Count=1;
			desc.SwapEffect=DXGI_SWAP_EFFECT_FLIP_DISCARD;
			DXGI_FORMAT fmts[]={DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,DXGI_FORMAT_B8G8R8X8_UNORM_SRGB};
			mSwapChain=m3DQueue->createSwapChain(wnd,desc,fmts,_countof(fmts));
			if(!mSwapChain)
			{
				DXGI_FORMAT fmts[]={DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_FORMAT_B8G8R8A8_UNORM,DXGI_FORMAT_B8G8R8X8_UNORM};
				mSwapChain=m3DQueue->createSwapChain(wnd,desc,fmts,_countof(fmts));
			}
		}
		if(0)
		{
			DXGI_SWAP_CHAIN_DESC desc={};
			desc.BufferDesc.Format=DXGI_FORMAT_B8G8R8A8_UNORM;
			desc.Windowed=TRUE;
			desc.BufferCount=3;
			desc.BufferUsage=DXGI_USAGE_BACK_BUFFER;
			desc.OutputWindow=wnd;
			desc.SampleDesc.Count=1;
			desc.SwapEffect=DXGI_SWAP_EFFECT_FLIP_DISCARD;
			mSwapChain=m3DQueue->createSwapChain(desc);
		}
		if(1)
		{
			VkSwapchainCreateInfoKHR info={};
			info.clipped=1;
			info.imageArrayLayers=1;
			info.imageColorSpace=VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
			info.imageFormat=VK_FORMAT_R8G8B8A8_SRGB;
			info.imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			info.minImageCount=2;
			info.presentMode=VK_PRESENT_MODE_MAILBOX_KHR;
			VkFormat fmts[]={VK_FORMAT_B8G8R8A8_SRGB,VK_FORMAT_A8B8G8R8_SRGB_PACK32,VK_FORMAT_R8G8B8_SRGB,VK_FORMAT_B8G8R8_SRGB};
			mSwapChain=m3DQueue->createSwapChain(wnd,info,fmts,_countof(fmts));
			if(!mSwapChain)
			{
				VkFormat fmts[]={VK_FORMAT_R8G8B8A8_UNORM,VK_FORMAT_B8G8R8A8_UNORM,VK_FORMAT_A8B8G8R8_UNORM_PACK32,VK_FORMAT_R8G8B8_UNORM,VK_FORMAT_B8G8R8_UNORM};
				mSwapChain=m3DQueue->createSwapChain(wnd,info,fmts,_countof(fmts));
			}
		}
	}

	NSDevilX::Void update()
	{
		mSwapChain->swapBuffers();
	}
};