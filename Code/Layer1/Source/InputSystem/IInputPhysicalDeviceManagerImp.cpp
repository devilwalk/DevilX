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

UInt16 NSDevilX::NSInputSystem::IPhysicalDeviceManagerImp::getDeviceCount() const
{
	return static_cast<UInt16>(mDeviceList.size());
}

IPhysicalDevice * NSDevilX::NSInputSystem::IPhysicalDeviceManagerImp::getDevice(UInt16 index) const
{
	return mDeviceList[index];
}
