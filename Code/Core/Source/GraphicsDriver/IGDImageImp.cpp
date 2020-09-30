#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IImageImp::IImageImp(IDeviceImp* device)
	:mDevice(device)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IImageImp::~IImageImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IImageImp::IImageImp(IDeviceImp* device,ID3D12Resource* resource)
	:NSGraphicsDriver::IImageImp(device)
	,mInternal(resource)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IImageImp::~IImageImp()
{
}

IImageView* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IImageImp::createView(const VkImageViewCreateInfo& info)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IImageImp::IImageImp(IDeviceImp* device,ID3D11Texture2D* resource)
	:NSGraphicsDriver::IImageImp(device)
	,mInternal(resource)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IImageImp::~IImageImp()
{
}

IImageView* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IImageImp::createView(const VkImageViewCreateInfo& info)
{
	return nullptr;
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IImageImp::IImageImp(IDeviceImp* device,VkImage resource)
	:NSGraphicsDriver::IImageImp(device)
	,mInternal(resource)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IImageImp::~IImageImp()
{
}

IImageView* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IImageImp::createView(const VkImageViewCreateInfo& info)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IImageImp::IImageImp(IDeviceImp* device,GLuint resource)
	:NSGraphicsDriver::IImageImp(device)
	,mInternal(resource)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IImageImp::~IImageImp()
{
}

IImageView* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IImageImp::createView(const VkImageViewCreateInfo& info)
{
	return nullptr;
}
