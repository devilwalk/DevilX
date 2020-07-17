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

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSD3D11::IDeviceImp::createSwapChain()
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

IQueue* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IDeviceImp::createQueue(IEnum::EQueue type)
{
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::IDeviceImp(GLenum context,NSGraphicsDriver::IPhysicalDeviceGroupImp* physicsDeviceGroup)
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

ISwapChain* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IDeviceImp::createSwapChain()
{
	return nullptr;
}
