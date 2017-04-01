#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CLoginPage
			:public TBaseObject<CLoginPage>
			,public NSGUISystem::IButtonEventCallback
			,public NSGUISystem::IEditBoxEventCallback
		{
		protected:
			NSGUISystem::IWindow * mGUIWindow;
		public:
			CLoginPage();
			~CLoginPage();

			// 通过 IButtonEventCallback 继承
			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent events) override;

			// 通过 IEditBoxEventCallback 继承
			virtual Void onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent events) override;
		};
		class CLogin
			:public CModule
			,public TBaseObject<CLogin>
		{
		public:
		protected:
			CLoginPage * mPage;
			TSharedReadData<Int32> mReturnCode;
		public:
			CLogin();
			~CLogin();
			Void doneMT(CServer::EReturnCode code);
			// 通过 CModule 继承
			virtual Void start() override;
			virtual Void update() override;
			virtual Void stop() override;
		};
	}
}