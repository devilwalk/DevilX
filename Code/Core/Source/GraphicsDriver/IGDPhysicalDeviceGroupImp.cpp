#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroupImp::IPhysicalDeviceGroupImp(IInstanceImp* instance)
	:mInstance(instance)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroupImp::~IPhysicalDeviceGroupImp()
{
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroupImp::getDeviceCount() const
{
	return static_cast<UInt32>(mDevices.size());
}

IPhysicalDevice* NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroupImp::getDevice(UInt32 index) const
{
	return mDevices[index];
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IPhysicalDeviceGroupImp::IPhysicalDeviceGroupImp(IDXGIAdapter* adapter,IInstanceImp* instance)
	:NSGraphicsDriver::IPhysicalDeviceGroupImp(instance)
	,mInternal(adapter)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IPhysicalDeviceGroupImp::~IPhysicalDeviceGroupImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceGroupImp::IPhysicalDeviceGroupImp(UInt32 group,IInstanceImp* instance)
	:NSGraphicsDriver::IPhysicalDeviceGroupImp(instance)
	,mInternal(group)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceGroupImp::~IPhysicalDeviceGroupImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IPhysicalDeviceGroupImp::IPhysicalDeviceGroupImp(IInstanceImp* instance)
	:NSGraphicsDriver::IPhysicalDeviceGroupImp(instance)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IPhysicalDeviceGroupImp::~IPhysicalDeviceGroupImp()
{
}