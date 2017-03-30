#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CApp::CApp()
	:mWindow(nullptr)
	,mRenderWindow(nullptr)
	,mGame(nullptr)
{
	CDesktop desktop;
	mWindow=DEVILX_NEW CWindow();
	mWindow->setSize(desktop.getSize()*0.6f);
	mWindow->setPosition((desktop.getSize()-mWindow->getSize())/2);
	NSGUISystem::getSystem()->initialize(mWindow);
	mRenderWindow=NSRenderSystem::getSystem()->createWindow(mWindow);
	mGame=DEVILX_NEW CGame();

	mGame->initialize();
}

NSDevilX::NSFightChess::CApp::~CApp()
{
	NSNetworkSystem::getSystem()->shutdown();
	NSGUISystem::getSystem()->shutdown();
	NSRenderSystem::getSystem()->shutdown();
	NSResourceSystem::getSystem()->shutdown();
	DEVILX_DELETE(mGame);
	DEVILX_DELETE(mWindow);
}

Void NSDevilX::NSFightChess::CApp::run()
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
		mGame->update();
		NSGUISystem::getSystem()->update();
		NSResourceSystem::getSystem()->update();
		NSRenderSystem::getSystem()->update();
		NSNetworkSystem::getSystem()->update();
	}
#endif
	DEVILX_DELETE(this);
}
