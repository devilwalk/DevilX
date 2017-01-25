#pragma once
namespace NSDevilX
{
	namespace NSUIEditor
	{
		class CApp
			:public TBaseObject<CApp>
			,public TSingletonEx<CApp>
		{
		protected:
			CWindow * mWindow;
			NSInputSystem::IVirtualDevice * mMouse;
			NSInputSystem::IVirtualDevice * mKeyboard;
		public:
			CApp();
			~CApp();
			CWindow * getWindow()const
			{
				return mWindow;
			}
			Void run();
		};
	}
}