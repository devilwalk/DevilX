#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CRegisterPage
			:public TBaseObject<CRegisterPage>
			,public NSGUISystem::IButtonEventCallback
			,public NSGUISystem::IEditBoxEventCallback
		{
		protected:
			NSGUISystem::IWindow * mGUIWindow;
		public:
			CRegisterPage();
			~CRegisterPage();

			// ͨ�� IButtonEventCallback �̳�
			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent events) override;

			// ͨ�� IEditBoxEventCallback �̳�
			virtual Void onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent events) override;
		};
		class CRegister
			:public TBaseObject<CRegister>
			,public CModule
		{
		public:
		protected:
			CRegisterPage * mPage;
			TSharedReadData<Int32> mReturnCode;
		public:
			CRegister();
			~CRegister();
			Void doneMT(CServer::EReturnCode code);

			// ͨ�� CModule �̳�
			virtual Void start() override;
			virtual Void update() override;
			virtual Void stop() override;
		};
	}
}