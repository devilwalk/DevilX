#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceGroupImp::IPhysicsDeviceGroupImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceGroupImp::~IPhysicsDeviceGroupImp()
{
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceGroupImp::getDeviceCount() const
{
	return static_cast<UInt32>(mDevices.size());
}

IPhysicsDevice* NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceGroupImp::getDevice(UInt32 index) const
{
	return mDevices[index];
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IPhysicsDeviceGroupImp::IPhysicsDeviceGroupImp(IDXGIAdapter* adapter)
	:mInternal(adapter)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IPhysicsDeviceGroupImp::~IPhysicsDeviceGroupImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicsDeviceGroupImp::IPhysicsDeviceGroupImp(UInt32 group)
	:mInternal(group)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicsDeviceGroupImp::~IPhysicsDeviceGroupImp()
{
}