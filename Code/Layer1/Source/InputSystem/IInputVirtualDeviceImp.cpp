#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
NSDevilX::NSInputSystem::IVirtualDeviceImp::IVirtualDeviceImp(const String & name,IPhysicalDeviceImp * physicalDevice,CWindow * window)
	:mName(name)
	,mPhysicalDevice(physicalDevice)
	,mWindow(window)
{}

NSDevilX::NSInputSystem::IVirtualDeviceImp::~IVirtualDeviceImp()
{}

Void NSDevilX::NSInputSystem::IVirtualDeviceImp::update()
{
	notify(EMessage_UpdateData);
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

CWindow * NSDevilX::NSInputSystem::IVirtualDeviceImp::getWindow() const
{
	return mWindow;
}
