#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
using namespace NSDirectX;
static BOOL FAR PASCAL DIEnumDevicesCallback(
	LPCDIDEVICEINSTANCE lpddi,
	LPVOID pvRef
	)
{
	CPhysicalDeviceManager * manager=static_cast<CPhysicalDeviceManager*>(pvRef);
	manager->addDevice(lpddi);
	return DIENUM_CONTINUE;
}

NSDevilX::NSInputSystem::NSDirectX::CPhysicalDeviceManager::CPhysicalDeviceManager()
{
	HRESULT hr=CSystem::getSingleton().getDirectInput()->EnumDevices(DI8DEVCLASS_ALL,DIEnumDevicesCallback,this,DIEDFL_ALLDEVICES);
	assert(SUCCEEDED(hr));
}

NSDevilX::NSInputSystem::NSDirectX::CPhysicalDeviceManager::~CPhysicalDeviceManager()
{}

Void NSDevilX::NSInputSystem::NSDirectX::CPhysicalDeviceManager::addDevice(LPCDIDEVICEINSTANCE instance)
{
	IPhysicalDeviceImp * device=nullptr;
	switch(instance->dwDevType&0xff)
	{
	case DI8DEVTYPE_MOUSE:
		device=DEVILX_NEW IPhysicalDeviceImp(IEnum::EPhysicalDeviceType_Mouse);
		break;
	case DI8DEVTYPE_KEYBOARD:
		device=DEVILX_NEW IPhysicalDeviceImp(IEnum::EPhysicalDeviceType_Keyboard);
		break;
	}
	if(device)
	{
		mDevices[device]=*instance;
	}
}

const DIDEVICEINSTANCE & NSDevilX::NSInputSystem::NSDirectX::CPhysicalDeviceManager::getInstance(IPhysicalDeviceImp * device) const
{
	// TODO: insert return statement here
	return mDevices.get(device);
}
