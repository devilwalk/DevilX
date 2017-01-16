#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
NSDevilX::NSInputSystem::IVirtualDeviceImp::IVirtualDeviceImp(const String & name,IPhysicalDeviceImp * physicalDevice)
	:mName(name)
	,mPhysicalDevice(physicalDevice)
{}

NSDevilX::NSInputSystem::IVirtualDeviceImp::~IVirtualDeviceImp()
{}

IMouse * NSDevilX::NSInputSystem::IVirtualDeviceImp::queryInterface_IMouse() const
{
	return nullptr;
}

IKeyboard * NSDevilX::NSInputSystem::IVirtualDeviceImp::queryInterface_IKeyboard() const
{
	return nullptr;
}

const String & NSDevilX::NSInputSystem::IVirtualDeviceImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IPhysicalDevice * NSDevilX::NSInputSystem::IVirtualDeviceImp::getPhysicalDevice() const
{
	return mPhysicalDevice;
}
