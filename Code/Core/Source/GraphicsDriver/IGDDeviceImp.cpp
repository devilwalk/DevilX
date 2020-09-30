#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IDeviceImp::IDeviceImp(IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:mPhysicsDeviceGroup(physicsDeviceGroup)
	,mDefaultMemoryAllocator(nullptr)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IDeviceImp::~IDeviceImp()
{
	DEVILX_DELETE(mDefaultMemoryAllocator);
}

IMemoryAllocator* NSDevilX::NSCore::NSGraphicsDriver::IDeviceImp::getDefaultMemoryAllocator() const
{
	return mDefaultMemoryAllocator;
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IDeviceImp::IDeviceImp(ID3D12Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,mInternal(dev)
{
	D3D12_COMMAND_QUEUE_DESC queue_desc={};
	queue_desc.Type=D3D12_COMMAND_LIST_TYPE_DIRECT;
	ID3D12CommandQueue* queue=nullptr;
	mInternal->CreateCommandQueue(&queue_desc,__uuidof(ID3D12CommandQueue),reinterpret_cast<VoidPtr*>(&queue));
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IDeviceImp::~IDeviceImp()
{
}

ICommandQueue* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IDeviceImp::createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice)
{
	D3D12_COMMAND_QUEUE_DESC queue_desc={};
	switch (type)
	{
	case NSDevilX::NSCore::NSGraphicsDriver::IEnum::ECommandQueue_3D:
		queue_desc.Type=D3D12_COMMAND_LIST_TYPE_DIRECT;
		break;
	case NSDevilX::NSCore::NSGraphicsDriver::IEnum::ECommandQueue_Compute:
		queue_desc.Type=D3D12_COMMAND_LIST_TYPE_COMPUTE;
		break;
	case NSDevilX::NSCore::NSGraphicsDriver::IEnum::ECommandQueue_PCIETransfer:
		queue_desc.Type=D3D12_COMMAND_LIST_TYPE_COPY;
		break;
	}
	if(physicalDevice)
		queue_desc.NodeMask=1<<physicalDevice->getIndex();
	ID3D12CommandQueue* queue=nullptr;
	mInternal->CreateCommandQueue(&queue_desc,__uuidof(ID3D12CommandQueue),reinterpret_cast<VoidPtr*>(&queue));
	auto ret=DEVILX_NEW ICommandQueueImp(this,queue);
	mQueues[type].push_back(ret);
	return ret;
}

ICommandAllocator* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IDeviceImp::createCommandAllocator(IEnum::ECommandQueue type)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::IDeviceImp(ID3D11Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,mInternal(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::~IDeviceImp()
{
}

ICommandQueue* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice)
{
	return nullptr;
}

ICommandAllocator* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createCommandAllocator(IEnum::ECommandQueue type)
{
	return nullptr;
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::IDeviceImp(VkDevice dev,IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,mInternal(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::~IDeviceImp()
{
}

ICommandQueue* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice)
{
	UInt32 physical_device_index=0;
	if(physicalDevice)
		physical_device_index=physicalDevice->getIndex();
	auto queue_family_infos=static_cast<IPhysicalDeviceImp*>(static_cast<IPhysicalDeviceGroupImp*>(mPhysicsDeviceGroup)->getDevices()[physical_device_index])->getQueueFamilies()[type];
	UInt32 use_count=-1;
	UInt32 queue_index=0;
	for(UInt32 i=0;i<queue_family_infos.sizeT<UInt32>();++i)
	{
		if(queue_family_infos[i].mUseCount<use_count)
		{
			queue_index=i;
			use_count=queue_family_infos[i].mUseCount;
		}
	}
	auto ret=DEVILX_NEW ICommandQueueImp(this,queue_family_infos[0].mQueueFamilyIndex,queue_index);
	mQueues[type].push_back(ret);
	return ret;
}

ICommandAllocator* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::createCommandAllocator(IEnum::ECommandQueue type)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::IDeviceImp(EGLContext context,NSGraphicsDriver::IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,ICommandQueueImp(this)
	,ICommandAllocatorImp(IEnum::ECommandQueue_3D,this)
	,ISwapChainImp(this)
	,mContext(context)
	,mSurface(EGL_NO_SURFACE)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::~IDeviceImp()
{
}

ICommandQueue* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice)
{
	return this;
}

ICommandAllocator* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createCommandAllocator(IEnum::ECommandQueue type)
{
	return this;
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
	if(mSurface!=EGL_NO_SURFACE)
		return nullptr;
	auto inst=static_cast<IInstanceImp*>(mPhysicsDeviceGroup->getInstance());
	TVector<EGLint> config_attrs;
	config_attrs.push_back(EGL_RENDERABLE_TYPE);
	if(inst->getMinorType()<=IEnum::EInstanceMinorType_GL_2_0)
	{
		config_attrs.push_back(EGL_OPENGL_BIT);
	}
	else
	{
		config_attrs.push_back(EGL_OPENGL_ES_BIT);
	}
	config_attrs.push_back(EGL_BUFFER_SIZE);
	switch(desc.Format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		config_attrs.push_back(32);
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		config_attrs.push_back(24);
		break;
	}
	switch(desc.Format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_ALPHA_SIZE);
		config_attrs.push_back(8);
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(8);
		break;
	case DXGI_FORMAT_B4G4R4A4_UNORM:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(4);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(4);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(4);
		config_attrs.push_back(EGL_ALPHA_SIZE);
		config_attrs.push_back(4);
		break;
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_ALPHA_SIZE);
		config_attrs.push_back(1);
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(6);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(5);
		break;
	}
	if(desc.SampleDesc.Count>1)
	{
		config_attrs.push_back(EGL_SAMPLE_BUFFERS);
		config_attrs.push_back(1);
		config_attrs.push_back(EGL_SAMPLES);
		config_attrs.push_back(desc.SampleDesc.Count);
	}
	config_attrs.push_back(EGL_SURFACE_TYPE);
	config_attrs.push_back(EGL_WINDOW_BIT);
	config_attrs.push_back(EGL_NONE);
	EGLConfig cfg;
	EGLint num_cfg;
	auto success=eglChooseConfig(inst->getDisplay(),&config_attrs[0],&cfg,1,&num_cfg)==EGL_TRUE;
	TVector<EGLint> attrs_list;
	attrs_list.push_back(EGL_RENDER_BUFFER);
	if(desc.BufferCount<2)
	{
		attrs_list.push_back(EGL_SINGLE_BUFFER);
	}
	else
	{
		attrs_list.push_back(EGL_BACK_BUFFER);
	}
	attrs_list.push_back(EGL_GL_COLORSPACE);
	switch(desc.Format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		attrs_list.push_back(EGL_GL_COLORSPACE_SRGB);
		break;
	default:
		attrs_list.push_back(EGL_GL_COLORSPACE_LINEAR);
	}
	attrs_list.push_back(EGL_NONE);
	mSurface=eglCreateWindowSurface(inst->getDisplay(),cfg,hwnd,&attrs_list[0]);
	if(EGL_NO_SURFACE==mSurface)
	{
		return nullptr;
	}
	eglMakeCurrent(inst->getDisplay(),mSurface,mSurface,mContext);
	return this;
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info)
{
	if(mSurface!=EGL_NO_SURFACE)
		return nullptr;
	auto inst=static_cast<IInstanceImp*>(mPhysicsDeviceGroup->getInstance());
	TVector<EGLint> config_attrs;
	config_attrs.push_back(EGL_RENDERABLE_TYPE);
	if(inst->getMinorType()<=IEnum::EInstanceMinorType_GL_2_0)
	{
		config_attrs.push_back(EGL_OPENGL_BIT);
	}
	else
	{
		config_attrs.push_back(EGL_OPENGL_ES_BIT);
	}
	config_attrs.push_back(EGL_BUFFER_SIZE);
	switch(info.imageFormat)
	{
	case VK_FORMAT_R8G8B8A8_SRGB:
	case VK_FORMAT_B8G8R8A8_SRGB:
	case VK_FORMAT_R8G8B8A8_UNORM:
	case VK_FORMAT_B8G8R8A8_UNORM:
		config_attrs.push_back(32);
		break;
	case VK_FORMAT_R8G8B8_SRGB:
	case VK_FORMAT_B8G8R8_SRGB:
	case VK_FORMAT_R8G8B8_UNORM:
	case VK_FORMAT_B8G8R8_UNORM:
		config_attrs.push_back(24);
		break;
	case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
	case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
	case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
	case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
	case VK_FORMAT_R5G6B5_UNORM_PACK16:
	case VK_FORMAT_B5G6R5_UNORM_PACK16:
		config_attrs.push_back(16);
		break;
	}
	switch(info.imageFormat)
	{
	case VK_FORMAT_R8G8B8A8_SRGB:
	case VK_FORMAT_B8G8R8A8_SRGB:
	case VK_FORMAT_R8G8B8A8_UNORM:
	case VK_FORMAT_B8G8R8A8_UNORM:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_ALPHA_SIZE);
		config_attrs.push_back(8);
		break;
	case VK_FORMAT_R8G8B8_SRGB:
	case VK_FORMAT_B8G8R8_SRGB:
	case VK_FORMAT_R8G8B8_UNORM:
	case VK_FORMAT_B8G8R8_UNORM:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(8);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(8);
		break;
	case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
	case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(4);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(4);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(4);
		config_attrs.push_back(EGL_ALPHA_SIZE);
		config_attrs.push_back(4);
		break;
	case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
	case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_ALPHA_SIZE);
		config_attrs.push_back(1);
		break;
	case VK_FORMAT_R5G6B5_UNORM_PACK16:
	case VK_FORMAT_B5G6R5_UNORM_PACK16:
		config_attrs.push_back(EGL_RED_SIZE);
		config_attrs.push_back(5);
		config_attrs.push_back(EGL_GREEN_SIZE);
		config_attrs.push_back(6);
		config_attrs.push_back(EGL_BLUE_SIZE);
		config_attrs.push_back(5);
		break;
	}
	config_attrs.push_back(EGL_SURFACE_TYPE);
	config_attrs.push_back(EGL_WINDOW_BIT);
	config_attrs.push_back(EGL_NONE);
	EGLConfig cfg;
	EGLint num_cfg;
	auto success=eglChooseConfig(inst->getDisplay(),&config_attrs[0],&cfg,1,&num_cfg)==EGL_TRUE;
	TVector<EGLint> attrs_list;
	attrs_list.push_back(EGL_RENDER_BUFFER);
	if(info.minImageCount<2)
	{
		attrs_list.push_back(EGL_SINGLE_BUFFER);
	}
	else
	{
		attrs_list.push_back(EGL_BACK_BUFFER);
	}
	attrs_list.push_back(EGL_GL_COLORSPACE);
	switch(info.imageFormat)
	{
	case VK_FORMAT_R8G8B8A8_SRGB:
	case VK_FORMAT_B8G8R8A8_SRGB:
	case VK_FORMAT_R8G8B8_SRGB:
	case VK_FORMAT_B8G8R8_SRGB:
		attrs_list.push_back(EGL_GL_COLORSPACE_SRGB);
		break;
	default:
		attrs_list.push_back(EGL_GL_COLORSPACE_LINEAR);
	}
	attrs_list.push_back(EGL_NONE);
	mSurface=eglCreateWindowSurface(inst->getDisplay(),cfg,hwnd,&attrs_list[0]);
	if(EGL_NO_SURFACE==mSurface)
	{
		return nullptr;
	}
	eglMakeCurrent(inst->getDisplay(),mSurface,mSurface,mContext);
	return this;
}

#endif

void NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::swapBuffers()
{
	auto inst=static_cast<IInstanceImp*>(mPhysicsDeviceGroup->getInstance());
	auto success=eglSwapBuffers(inst->getDisplay(),mSurface);
	assert(success);
}
