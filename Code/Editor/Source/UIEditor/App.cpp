#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUIEditor;
Void main()
{
	CApp::getSingleton().run();
}

NSDevilX::NSUIEditor::CApp::CApp()
	:mWindow(nullptr)
	,mMouse(nullptr)
	,mKeyboard(nullptr)
{
	mWindow=DEVILX_NEW CWindow();
	getWindow()->setSize(CSInt2(800,600));
	for(UInt32 i=0;i<NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDeviceCount();++i)
	{
		auto dev=NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDevice(i);
		if((!mMouse)&&(NSInputSystem::IEnum::EPhysicalDeviceType_Mouse==dev->getType()))
			mMouse=NSInputSystem::getSystem()->getVirtualDeviceManager()->createDevice("EditorMouse",dev);
		if((!mMouse)&&(NSInputSystem::IEnum::EPhysicalDeviceType_Keyboard==dev->getType()))
			mKeyboard=NSInputSystem::getSystem()->getVirtualDeviceManager()->createDevice("EditorKeyboard",dev);
	}
}

NSDevilX::NSUIEditor::CApp::~CApp()
{
	NSInputSystem::getSystem()->shutdown();
	DEVILX_DELETE(mWindow);
}

Void NSDevilX::NSUIEditor::CApp::run()
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	MSG msg={0};
	while(true)
	{
		if(PeekMessage(&msg,static_cast<HWND>(getWindow()->getHandle()),0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
#endif
}
