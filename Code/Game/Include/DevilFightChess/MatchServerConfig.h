#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchServerConfig;
		class CMatchServerConfigPage
			:public TBaseObject<CMatchServerConfigPage>
			,public NSGUISystem::IButtonEventCallback
			,public NSGUISystem::IEditBoxEventCallback
		{
		protected:
			CMatchServerConfig * const mModule;
			NSGUISystem::IWindow * mGUIWindow;
		public:
			CMatchServerConfigPage(CMatchServerConfig * config);
			~CMatchServerConfigPage();

			// ͨ�� IButtonEventCallback �̳�
			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent events) override;

			// ͨ�� IEditBoxEventCallback �̳�
			virtual Void onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent events) override;
		};
		class CMatchServerConfig
			:public TBaseObject<CMatchServerConfig>
			,public CModule
		{
		protected:
			CMatchServerConfigPage * mPage;
			TSharedReadData<Int32> mReturnCode;
		public:
			CMatchServerConfig();
			~CMatchServerConfig();

			// ͨ�� CModule �̳�
			virtual Void start() override;
			virtual Void update() override;
			virtual Void stop() override;
		};
	}
}