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

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::IQueueImp::createSwapChain(DXGI_SWAP_CHAIN_DESC& desc)
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
	return static_cast<IQueue*>(this)->createSwapChain(desc.OutputWindow,desc1,&full_screen_desc);
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::IQueueImp(IDeviceImp* dev,ID3D12CommandQueue* queue)
	:NSGraphicsDriver::IQueueImp(dev)
	,mInternal(queue)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::~IQueueImp()
{
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
	auto ret=DEVILX_NEW NSD3D::ISwapChainImp(this,hwnd,desc,fullscreenDesc);
	mSwapChains.push_back(ret);
	return ret;
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info)
{
	DXGI_SWAP_CHAIN_DESC1 desc={};
	switch(info.compositeAlpha)
	{
	case VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR:
		desc.AlphaMode=DXGI_ALPHA_MODE_IGNORE;
		break;
	case VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR:
		desc.AlphaMode=DXGI_ALPHA_MODE_PREMULTIPLIED;
		break;
	case VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR:
		desc.AlphaMode=DXGI_ALPHA_MODE_STRAIGHT;
		break;
	case VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR:
		desc.AlphaMode=DXGI_ALPHA_MODE_UNSPECIFIED;
		break;
	default:
		desc.AlphaMode=DXGI_ALPHA_MODE_IGNORE;
	}
	desc.BufferCount=info.minImageCount;
	desc.BufferUsage=0;
	if((info.imageUsage&VK_IMAGE_USAGE_SAMPLED_BIT)
		||(info.imageUsage&VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
		)
	{
		desc.BufferUsage|=DXGI_USAGE_SHADER_INPUT;
	}
	if(info.imageUsage&VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
	{
		desc.BufferUsage|=DXGI_USAGE_BACK_BUFFER;
	}
	if(info.imageUsage&VK_IMAGE_USAGE_STORAGE_BIT)
	{
		desc.BufferUsage|=DXGI_USAGE_UNORDERED_ACCESS;
	}
	switch(info.imageFormat)
	{
	case VK_FORMAT_R8G8B8A8_SRGB:
		desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		break;
	case VK_FORMAT_R8G8B8A8_UNORM:
		desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
		break;
	case VK_FORMAT_B8G8R8A8_SNORM:
		desc.Format=DXGI_FORMAT_B8G8R8A8_UNORM;
		break;
	case VK_FORMAT_B8G8R8A8_SRGB:
		desc.Format=DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		break;
	case VK_FORMAT_B8G8R8_SNORM:
	case VK_FORMAT_R8G8B8_SNORM:
		desc.Format=DXGI_FORMAT_B8G8R8X8_UNORM;
		break;
	case VK_FORMAT_B8G8R8_SRGB:
	case VK_FORMAT_R8G8B8_SRGB:
		desc.Format=DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		break;
	case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
	case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
		desc.Format=DXGI_FORMAT_B5G5R5A1_UNORM;
		break;
	case VK_FORMAT_R5G6B5_UNORM_PACK16:
	case VK_FORMAT_B5G6R5_UNORM_PACK16:
		desc.Format=DXGI_FORMAT_B5G6R5_UNORM;
		break;
	case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
	case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
		desc.Format=DXGI_FORMAT_B4G4R4A4_UNORM;
		break;
	}
	desc.Height=info.imageExtent.height;
	desc.SampleDesc.Count=1;
	desc.Scaling=DXGI_SCALING_NONE;
	desc.Stereo=FALSE;
	desc.SwapEffect=DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Width=info.imageExtent.width;
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC full_screen_desc={};
	full_screen_desc.Windowed=TRUE;
	if(info.pNext&&(static_cast<const VkSurfaceFullScreenExclusiveWin32InfoEXT*>(info.pNext)->sType==VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT))
	{
		full_screen_desc.Windowed=FALSE;
	}
	return createSwapChain(hwnd,desc,&full_screen_desc);
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::IQueueImp(IDeviceImp* dev,VkQueue queue,UInt32 familyIndex)
	:NSGraphicsDriver::IQueueImp(dev)
	,mInternal(queue)
	,mFamilyIndex(familyIndex)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::~IQueueImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
	VkSwapchainCreateInfoKHR info={};
	info.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	VkWin32SurfaceCreateInfoKHR surface_create_info={};
	surface_create_info.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surface_create_info.hinstance=GetModuleHandle(NULL);
	surface_create_info.hwnd=hwnd;
	vkCreateWin32SurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),&surface_create_info,nullptr,&info.surface);
	info.minImageCount=desc.BufferCount;
	switch(desc.Format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		info.imageFormat=VK_FORMAT_R8G8B8A8_SRGB;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		info.imageFormat=VK_FORMAT_B8G8R8A8_SRGB;
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		info.imageFormat=VK_FORMAT_R8G8B8A8_SNORM;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		info.imageFormat=VK_FORMAT_B8G8R8A8_SNORM;
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		info.imageFormat=VK_FORMAT_B8G8R8_SRGB;
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		info.imageFormat=VK_FORMAT_B8G8R8_UNORM;
		break;
	case DXGI_FORMAT_B4G4R4A4_UNORM:
		info.imageFormat=VK_FORMAT_B4G4R4A4_UNORM_PACK16;
		break;
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		info.imageFormat=VK_FORMAT_B5G5R5A1_UNORM_PACK16;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		info.imageFormat=VK_FORMAT_B5G6R5_UNORM_PACK16;
		break;
	}
	info.imageColorSpace=VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	RECT rc={};
	GetClientRect(hwnd,&rc);
	if(desc.Height)
		info.imageExtent.height=desc.Height;
	else
		info.imageExtent.height=rc.bottom-rc.top;
	if(desc.Width)
		info.imageExtent.width=desc.Width;
	else
		info.imageExtent.width=rc.right-rc.left;
	info.imageArrayLayers=1;
	info.imageUsage=0;
	if(desc.BufferUsage&DXGI_USAGE_BACK_BUFFER)
	{

	}
	if(desc.BufferUsage&DXGI_USAGE_RENDER_TARGET_OUTPUT)
	{
		info.imageUsage|=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	}
	if(desc.BufferUsage&DXGI_USAGE_SHADER_INPUT)
	{
		info.imageUsage|=VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT|VK_IMAGE_USAGE_SAMPLED_BIT;
	}
	if(desc.BufferUsage&DXGI_USAGE_UNORDERED_ACCESS)
	{
		info.imageUsage|=VK_IMAGE_USAGE_STORAGE_BIT;
	}
	info.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
	info.preTransform=VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR;
	switch(desc.AlphaMode)
	{
	case DXGI_ALPHA_MODE_IGNORE:
		info.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		break;
	case DXGI_ALPHA_MODE_PREMULTIPLIED:
		info.compositeAlpha=VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
		break;
	case DXGI_ALPHA_MODE_STRAIGHT:
		info.compositeAlpha=VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
		break;
	case DXGI_ALPHA_MODE_UNSPECIFIED:
		info.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		break;
	}
	info.presentMode=VK_PRESENT_MODE_MAILBOX_KHR;
	info.clipped=VK_TRUE;
	info.queueFamilyIndexCount=1;
	uint32_t queue_family=static_cast<IPhysicalDeviceImp*>(mDevice->getPhysicalDeviceGroup()->getDevice(0))->getQueueFamilies()[IEnum::EQueue_3D][0].mQueueFamilyIndex;
	info.pQueueFamilyIndices=&queue_family;
	return createSwapChain(hwnd,info);
}
#endif

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info)
{
	auto cpy_info=info;
	if(cpy_info.surface==0)
	{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
		VkWin32SurfaceCreateInfoKHR surface_create_info={};
		surface_create_info.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surface_create_info.hinstance=GetModuleHandle(NULL);
		surface_create_info.hwnd=hwnd;
		vkCreateWin32SurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),&surface_create_info,nullptr,&cpy_info.surface);
#endif
	}
	VkBool32 surface_support=VK_FALSE;
	if((VK_SUCCESS!=vkGetPhysicalDeviceSurfaceSupportKHR(static_cast<IPhysicalDeviceImp*>(mDevice->getPhysicalDeviceGroup()->getDevices()[0])->getInternal(),info.pQueueFamilyIndices[0],cpy_info.surface,&surface_support))
		&&(!surface_support))
	{
		vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),cpy_info.surface,nullptr);
		return nullptr;
	}
	VkPhysicalDeviceSurfaceInfo2KHR surface_info={};
	surface_info.sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
	surface_info.surface=cpy_info.surface;
	VkSurfaceCapabilities2KHR surface_cap={};
	surface_cap.sType=VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
	if(VK_SUCCESS!=vkGetPhysicalDeviceSurfaceCapabilities2KHR(static_cast<IPhysicalDeviceImp*>(mDevice->getPhysicalDeviceGroup()->getDevices()[0])->getInternal(),&surface_info,&surface_cap))
	{
		vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),cpy_info.surface,nullptr);
		return nullptr;
	}
	if(!(cpy_info.preTransform&surface_cap.surfaceCapabilities.supportedTransforms))
	{
		cpy_info.preTransform=surface_cap.surfaceCapabilities.currentTransform;
	}
	switch(cpy_info.presentMode)
	{
	case VK_PRESENT_MODE_IMMEDIATE_KHR:
	case VK_PRESENT_MODE_MAILBOX_KHR:
	case VK_PRESENT_MODE_FIFO_KHR:
	case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
		if((cpy_info.imageUsage&surface_cap.surfaceCapabilities.supportedUsageFlags)!=cpy_info.imageUsage)
		{
			vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),cpy_info.surface,nullptr);
			return nullptr;
		}
		break;
	}
	uint32_t support_count=0;
	if(VK_SUCCESS!=vkGetPhysicalDeviceSurfaceFormats2KHR(static_cast<IPhysicalDeviceImp*>(mDevice->getPhysicalDeviceGroup()->getDevices()[0])->getInternal(),&surface_info,&support_count,nullptr))
	{
		vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),cpy_info.surface,nullptr);
		return nullptr;
	}
	TVector(VkSurfaceFormat2KHR) surface_formats(support_count);
	for(auto& fmt:surface_formats)
	{
		fmt.sType=VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
	}
	vkGetPhysicalDeviceSurfaceFormats2KHR(static_cast<IPhysicalDeviceImp*>(mDevice->getPhysicalDeviceGroup()->getDevices()[0])->getInternal(),&surface_info,&support_count,&surface_formats[0]);
	Boolean fmt_support=false;
	for(auto const& fmt:surface_formats)
	{
		if((fmt.surfaceFormat.colorSpace==cpy_info.imageColorSpace)
			&&(fmt.surfaceFormat.format==cpy_info.imageFormat))
		{
			fmt_support=true;
			break;
		}
	}
	if(!fmt_support)
	{
		for(auto const& fmt:surface_formats)
		{
			if(fmt.surfaceFormat.colorSpace==cpy_info.imageColorSpace)
			{
				switch(fmt.surfaceFormat.format)
				{
				case VK_FORMAT_R8G8B8A8_SRGB:
				case VK_FORMAT_R8G8B8_SRGB:
				case VK_FORMAT_B8G8R8A8_SRGB:
				case VK_FORMAT_B8G8R8_SRGB:
				case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
					switch(cpy_info.imageFormat)
					{
					case VK_FORMAT_R8G8B8A8_SRGB:
					case VK_FORMAT_R8G8B8_SRGB:
					case VK_FORMAT_B8G8R8A8_SRGB:
					case VK_FORMAT_B8G8R8_SRGB:
					case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
						fmt_support=true;
						break;
					}
					break;
				case VK_FORMAT_R8G8B8A8_UNORM:
				case VK_FORMAT_R8G8B8_UNORM:
				case VK_FORMAT_B8G8R8A8_UNORM:
				case VK_FORMAT_B8G8R8_UNORM:
				case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
					switch(cpy_info.imageFormat)
					{
					case VK_FORMAT_R8G8B8A8_UNORM:
					case VK_FORMAT_R8G8B8_UNORM:
					case VK_FORMAT_B8G8R8A8_UNORM:
					case VK_FORMAT_B8G8R8_UNORM:
					case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
						fmt_support=true;
						break;
					}
					break;
				}
				if(fmt_support)
				{
					cpy_info.imageFormat=fmt.surfaceFormat.format;
					break;
				}
			}
		}
	}
	if(!fmt_support)
	{
		vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),cpy_info.surface,nullptr);
		return nullptr;
	}
	if(VK_SUCCESS!=vkGetPhysicalDeviceSurfacePresentModesKHR(static_cast<IPhysicalDeviceImp*>(mDevice->getPhysicalDeviceGroup()->getDevices()[0])->getInternal(),cpy_info.surface,&support_count,nullptr))
	{
		vkDestroySurfaceKHR(static_cast<IInstanceImp*>(mDevice->getPhysicalDeviceGroup()->getInstance())->getInternal(),cpy_info.surface,nullptr);
		return nullptr;
	}
	TVector(VkPresentModeKHR) present_modes(support_count);
	vkGetPhysicalDeviceSurfacePresentModesKHR(static_cast<IPhysicalDeviceImp*>(mDevice->getPhysicalDeviceGroup()->getDevices()[0])->getInternal(),cpy_info.surface,&support_count,&present_modes[0]);
	if(!present_modes.has(cpy_info.presentMode))
	{
		cpy_info.presentMode=present_modes[0];
	}
	auto ret=DEVILX_NEW ISwapChainImp(this,cpy_info);
	mSwapChains.push_back(ret);
	return ret;
}
