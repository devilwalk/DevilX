#pragma once
#include "InputConfig.h"
#include "Scene.h"
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CApp
			:public TBaseObject<CApp>
			,public TSingletonEx<CApp>
		{
		protected:
			CWindow * mWindow;
			NSInputSystem::IVirtualDevice * mMouse;
			NSInputSystem::IVirtualDevice * mKeyboard;
			NSRenderSystem::IWindow * mRenderWindow;
			CInputConfigManager * mInputConfigManager;
			CScene * mScene;
		public:
			CApp();
			~CApp();
			CWindow * getWindow()const
			{
				return mWindow;
			}
			NSInputSystem::IVirtualDevice * getMouse()const
			{
				return mMouse;
			}
			NSInputSystem::IVirtualDevice * getKeyboard()const
			{
				return mKeyboard;
			}
			CInputConfigManager * getInputConfigManager()const
			{
				return mInputConfigManager;
			}
			Void setScene(CScene * scene)
			{
				mScene=scene;
			}
			CScene * getScene()const
			{
				return mScene;
			}
			Void run();
		};
	}
}