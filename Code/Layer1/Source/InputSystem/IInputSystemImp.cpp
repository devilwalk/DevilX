#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
NSDevilX::NSInputSystem::ISystemImp::ISystemImp()
	:mPhysicalDeviceManager(0)
	,mVirtualDeviceManager(0)
{
	mPhysicalDeviceManager=DEVILX_NEW IPhysicalDeviceManagerImp;
	mVirtualDeviceManager=DEVILX_NEW IVirtualDeviceManagerImp;
}

NSDevilX::NSInputSystem::ISystemImp::~ISystemImp()
{
	notify(EMessage_BeginDestruction);
	DEVILX_DELETE(mPhysicalDeviceManager);
	DEVILX_DELETE(mVirtualDeviceManager);
	notify(EMessage_EndDestruction);
}

Void NSDevilX::NSInputSystem::ISystemImp::shutdown()
{
	DEVILX_DELETE(this);
}

Void NSDevilX::NSInputSystem::ISystemImp::update()
{
	static_cast<IVirtualDeviceManagerImp*>(getVirtualDeviceManager())->update();
}

IPhysicalDeviceManager * NSDevilX::NSInputSystem::ISystemImp::getPhysicalDeviceManager() const
{
	return mPhysicalDeviceManager;
}

IVirtualDeviceManager * NSDevilX::NSInputSystem::ISystemImp::getVirtualDeviceManager() const
{
	return mVirtualDeviceManager;
}