#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
NSDevilX::NSInputSystem::IPhysicalDeviceManagerImp::IPhysicalDeviceManagerImp()
{}

NSDevilX::NSInputSystem::IPhysicalDeviceManagerImp::~IPhysicalDeviceManagerImp()
{
	for(auto device:mDeviceList)
	{
		DEVILX_DELETE(device);
	}
}

UInt32 NSDevilX::NSInputSystem::IPhysicalDeviceManagerImp::getDeviceCount() const
{
	return static_cast<UInt32>(mDeviceList.size());
}

IPhysicalDevice * NSDevilX::NSInputSystem::IPhysicalDeviceManagerImp::getDevice(UInt32 index) const
{
	return mDeviceList[index];
}
