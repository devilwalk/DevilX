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
			NSRenderSystem::IWindow * mRenderWindow;
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