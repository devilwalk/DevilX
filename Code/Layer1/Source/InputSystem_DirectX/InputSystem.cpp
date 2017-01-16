#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
using namespace NSDirectX;
ISystem * NSDevilX::NSInputSystem::getSystem()
{
	static CSystem * system=DEVILX_NEW CSystem;
	return ISystemImp::getSingletonPtr();
}
NSDevilX::NSInputSystem::NSDirectX::CSystem::CSystem()
	:mDirectInput(0)
	,mPhysicalDeviceManager(0)
	,mVirtualDeviceManager(0)
{
	DEVILX_NEW ISystemImp;
	HRESULT hr=DirectInput8Create(GetModuleHandle(nullptr),DIRECTINPUT_VERSION,IID_IDirectInput8,reinterpret_cast<VoidPtr*>(&mDirectInput),nullptr);
	CHECK_API_SUCCESSED;
	mPhysicalDeviceManager=DEVILX_NEW CPhysicalDeviceManager;
	mVirtualDeviceManager=DEVILX_NEW CVirtualDeviceManager;
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginDestruction,False);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_UpdateData,False);
}

NSDevilX::NSInputSystem::NSDirectX::CSystem::~CSystem()
{
	DEVILX_DELETE(mPhysicalDeviceManager);
	DEVILX_DELETE(mVirtualDeviceManager);
	mDirectInput->Release();
}

void NSDevilX::NSInputSystem::NSDirectX::CSystem::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_BeginDestruction:
		DEVILX_DELETE(this);
		break;
	case ISystemImp::EMessage_UpdateData:
		mVirtualDeviceManager->update();
		break;
	}
}
