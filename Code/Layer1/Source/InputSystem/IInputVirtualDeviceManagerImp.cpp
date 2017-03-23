#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::IVirtualDeviceManagerImp()
{}

NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::~IVirtualDeviceManagerImp()
{}

Void NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::update()
{
	for(auto const & pair:mDeviceList)
		pair.second->update();
}

IMouse * NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::createMouse(const String & name,IPhysicalDevice * device,CWindow * window)
{
	return static_cast<IMouseImp*>(_createDevice(name,device,window));
}

IKeyboard * NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::createKeyboard(const String & name,IPhysicalDevice * device,CWindow * window)
{
	return static_cast<IKeyboardImp*>(_createDevice(name,device,window));
}

Void NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::destroyDevice(IVirtualDevice * device)
{
	IVirtualDeviceImp * ret=static_cast<IVirtualDeviceImp*>(device);
	notify(EMessage_BeginDeviceDestroy);
	mDeviceList.destroy(ret->getName());
	notify(EMessage_EndDeviceDestroy);
}

IVirtualDevice * NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::getDevice(const String & name) const
{
	if(mDeviceList.has(name))
		return mDeviceList.get(name);
	else
		return nullptr;
}

IVirtualDeviceImp * NSDevilX::NSInputSystem::IVirtualDeviceManagerImp::_createDevice(const String & name,IPhysicalDevice * device,CWindow * window)
{
	assert(nullptr==getDevice(name));
	IVirtualDeviceImp * ret=nullptr;
	notify(EMessage_BeginDeviceCreate,static_cast<IPhysicalDeviceImp*>(device));
	switch(device->getType())
	{
	case IEnum::EPhysicalDeviceType_Mouse:
		ret=DEVILX_NEW IMouseImp(name,static_cast<IPhysicalDeviceImp*>(device),window);
		break;
	case IEnum::EPhysicalDeviceType_Keyboard:
		ret=DEVILX_NEW IKeyboardImp(name,static_cast<IPhysicalDeviceImp*>(device),window);
		break;
	}
	mDeviceList[name]=ret;
	notify(EMessage_EndDeviceCreate,ret);
	return ret;
}
