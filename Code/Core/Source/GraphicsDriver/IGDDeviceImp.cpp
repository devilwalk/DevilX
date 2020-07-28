#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IDeviceImp::IDeviceImp(IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:mPhysicsDeviceGroup(physicsDeviceGroup)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IDeviceImp::~IDeviceImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IDeviceImp::IDeviceImp(ID3D12Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,mInternal(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IDeviceImp::~IDeviceImp()
{
}

IQueue* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IDeviceImp::createQueue(IEnum::EQueue type)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::IDeviceImp(ID3D11Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,IQueueImp(this)
	,mInternal(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::~IDeviceImp()
{
}

IQueue* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createQueue(IEnum::EQueue type)
{
	return this;
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createSwapChain(DXGI_SWAP_CHAIN_DESC& desc)
{
	auto ret=DEVILX_NEW NSD3D::ISwapChainImp(this,desc);
	mSwapChains.push_back(ret);
	return ret;
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
	auto ret=DEVILX_NEW NSD3D::ISwapChainImp(this,hwnd,desc,fullscreenDesc);
	mSwapChains.push_back(ret);
	return ret;
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info)
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

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::IDeviceImp(VkDevice dev,IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,mInternal(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::~IDeviceImp()
{
}

IQueue* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::createQueue(IEnum::EQueue type)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::IDeviceImp(EGLContext context,NSGraphicsDriver::IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,mContext(context)
	,mSurface(EGL_NO_SURFACE)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::~IDeviceImp()
{
}

IQueue* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createQueue(IEnum::EQueue type)
{
	return this;
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createSwapChain(DXGI_SWAP_CHAIN_DESC& desc)
{
	if(mSurface!=EGL_NO_SURFACE)
		return nullptr;
	auto inst=static_cast<IInstanceImp*>(mPhysicsDeviceGroup->getInstance());
	TVector(EGLint) config_attrs;
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
	switch(desc.BufferDesc.Format)
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
	switch(desc.BufferDesc.Format)
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
	TVector(EGLAttrib) attrs_list;
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
	switch(desc.BufferDesc.Format)
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
	mSurface=eglCreateWindowSurface(inst->getDisplay(),cfg,desc.OutputWindow,&attrs_list[0]);
	if(EGL_NO_SURFACE==mSurface)
	{
		return nullptr;
	}
	eglMakeCurrent(inst->getDisplay(),mSurface,mSurface,mContext);
	return this;
}

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
	if(mSurface!=EGL_NO_SURFACE)
		return nullptr;
	auto inst=static_cast<IInstanceImp*>(mPhysicsDeviceGroup->getInstance());
	TVector(EGLint) config_attrs;
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
	TVector(EGLAttrib) attrs_list;
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
	TVector(EGLint) config_attrs;
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
	TVector(EGLAttrib) attrs_list;
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
