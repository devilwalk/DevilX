#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSApplication;

NSDevilX::NSApplication::IApplication * NSDevilX::NSApplication::getApp()
{
	return IApplicationImp::getSingletonPtr();
}

NSDevilX::NSApplication::IApplicationImp::IApplicationImp()
	:mWindow(nullptr)
	,mRenderWindow(nullptr)
{
	CDesktop desktop;
	mWindow=DEVILX_NEW CWindow();
	mWindow->setSize(desktop.getSize()*0.5f);
	mWindow->setPosition((desktop.getSize()-mWindow->getSize())/2);
	mRenderWindow=NSRenderSystem::getSystem()->createWindow(mWindow);
}

NSDevilX::NSApplication::IApplicationImp::~IApplicationImp()
{
	NSNetworkSystem::getSystem()->shutdown();
	NSRenderSystem::getSystem()->shutdown();
	DEVILX_DELETE(getWindow());
}

CWindow * NSDevilX::NSApplication::IApplicationImp::getWindow() const
{
	return mWindow;
}

Void NSDevilX::NSApplication::IApplicationImp::run()
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	MSG msg={0};
	while(WM_QUIT!=msg.message)
	{
		if(PeekMessage(&msg,static_cast<HWND>(mWindow->getHandle()),0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		NSNetworkSystem::getSystem()->update();
		NSRenderSystem::getSystem()->update();
	}
#endif
}

Void NSDevilX::NSApplication::IApplicationImp::shutdown()
{
	DEVILX_DELETE(this);
}
