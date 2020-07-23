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

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
	auto inst=static_cast<NSD3D::IInstanceImp*>(mPhysicsDeviceGroup->getInstance());
	IDXGISwapChain1* swapchain=nullptr;
	inst->getInternal2()->CreateSwapChainForHwnd(mInternal,hwnd,&desc,fullscreenDesc,nullptr,&swapchain);
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

IQueue* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::createQueue(IEnum::EQueue type)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::IDeviceImp(EGLContext context,NSGraphicsDriver::IPhysicalDeviceGroupImp* physicsDeviceGroup)
	:NSGraphicsDriver::IDeviceImp(physicsDeviceGroup)
	,mInternal(context)
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
ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc)
{
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
	auto surface=eglCreateWindowSurface(inst->getDisplay(),cfg,hwnd,&attrs_list[0]);
	return nullptr;
}
#endif
