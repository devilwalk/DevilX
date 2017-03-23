#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
using namespace NSDirectX;
NSDevilX::NSInputSystem::NSDirectX::CVirtualDeviceManager::CVirtualDeviceManager()
{
	static_cast<IVirtualDeviceManagerImp*>(ISystemImp::getSingleton().getVirtualDeviceManager())->addListener(this,IVirtualDeviceManagerImp::EMessage_EndDeviceCreate,False);
}

NSDevilX::NSInputSystem::NSDirectX::CVirtualDeviceManager::~CVirtualDeviceManager()
{}

void NSDevilX::NSInputSystem::NSDirectX::CVirtualDeviceManager::onMessage(IVirtualDeviceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IVirtualDeviceManagerImp::EMessage_EndDeviceCreate:
		_createVirtualDevice(static_cast<IVirtualDeviceImp*>(data));
		break;
	}
}

Void NSDevilX::NSInputSystem::NSDirectX::CVirtualDeviceManager::_createVirtualDevice(IVirtualDeviceImp * device)
{
	CVirtualDevice * virtual_device=nullptr;
	switch(device->getPhysicalDevice()->getType())
	{
	case IEnum::EPhysicalDeviceType_Mouse:
		virtual_device=DEVILX_NEW CMouse(device);
		break;
	case IEnum::EPhysicalDeviceType_Keyboard:
		virtual_device=DEVILX_NEW CKeyboard(device);
		break;
	}
	if(virtual_device)
	{
		mDevices[device]=virtual_device;
	}
}
