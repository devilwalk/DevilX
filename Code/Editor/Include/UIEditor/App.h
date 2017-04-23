#pragma once
#include "MainFrame.h"
namespace NSDevilX
{
	namespace NSUIEditor
	{
		class CApp
			:public TBaseObject<CApp>
			,public TSingletonEx<CApp>
		{
		protected:
			CMainFrame * mMainFrame;
			CWindow * mWindow;
			NSRenderSystem::IWindow * mRenderWindow;
		public:
			CApp();
			~CApp();
			CMainFrame * getMainFrame()const{ return mMainFrame; }
			CWindow * getWindow()const
			{
				return mWindow;
			}
			Void run();
		};
	}
}