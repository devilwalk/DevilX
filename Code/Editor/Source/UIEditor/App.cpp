#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUIEditor;

NSDevilX::NSUIEditor::CApp::CApp()
	:mWindow(nullptr)
	,mRenderWindow(nullptr)
	,mMainFrame(nullptr)
{
	CDesktop desktop;
	mWindow=DEVILX_NEW CWindow();
	mWindow->setSize(desktop.getSize()*0.6f);
	mWindow->setPosition((desktop.getSize()-mWindow->getSize())/2);
	NSGUISystem::getSystem()->initialize(mWindow);
	mRenderWindow=NSRenderSystem::getSystem()->createWindow(mWindow);
}

NSDevilX::NSUIEditor::CApp::~CApp()
{
	DEVILX_DELETE(getMainFrame());
	NSGUISystem::getSystem()->shutdown();
	NSRenderSystem::getSystem()->shutdown();
	DEVILX_DELETE(mWindow);
}

Void NSDevilX::NSUIEditor::CApp::run()
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
		else
		{
			NSRenderSystem::getSystem()->update();
		}
	}
#endif
}
