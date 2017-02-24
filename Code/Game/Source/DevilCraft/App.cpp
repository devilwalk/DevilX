#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSDevilCraft;

NSDevilX::NSDevilCraft::CApp::CApp()
	:mWindow(nullptr)
	,mMouse(nullptr)
	,mKeyboard(nullptr)
	,mRenderWindow(nullptr)
	,mInputConfigManager(nullptr)
	,mScene(nullptr)
{
	CDesktop desktop;
	mWindow=DEVILX_NEW CWindow();
	getWindow()->setPosition((desktop.getSize()-getWindow()->getSize())/2);
	getWindow()->setSize(desktop.getSize()*0.6);
	for(UInt32 i=0;i<NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDeviceCount();++i)
	{
		auto dev=NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDevice(i);
		if((!mMouse)&&(NSInputSystem::IEnum::EPhysicalDeviceType_Mouse==dev->getType()))
			mMouse=NSInputSystem::getSystem()->getVirtualDeviceManager()->createDevice("GameMouse",dev);
		if((!mKeyboard)&&(NSInputSystem::IEnum::EPhysicalDeviceType_Keyboard==dev->getType()))
			mKeyboard=NSInputSystem::getSystem()->getVirtualDeviceManager()->createDevice("GameKeyboard",dev);
	}
	mRenderWindow=NSRenderSystem::getSystem()->createWindow(getWindow()->getHandle());
	mInputConfigManager=DEVILX_NEW CInputConfigManager();
}

NSDevilX::NSDevilCraft::CApp::~CApp()
{
	DEVILX_DELETE(mInputConfigManager);
	NSRenderSystem::getSystem()->shutdown();
	NSInputSystem::getSystem()->shutdown();
	DEVILX_DELETE(mWindow);
}

Void NSDevilX::NSDevilCraft::CApp::run()
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	MSG msg={0};
	while(WM_QUIT!=msg.message)
	{
		if(PeekMessage(&msg,static_cast<HWND>(getWindow()->getHandle()),0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		NSInputSystem::getSystem()->update();
		if(getScene())
			getScene()->preUpdate();
		NSPhysicalSystem::getSystem()->update();
		if(getScene())
			getScene()->update();
		NSRenderSystem::getSystem()->update();
		NSNetworkSystem::getSystem()->update();
	}
#endif
}
