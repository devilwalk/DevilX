#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CLoginPage
			:public TBaseObject<CLoginPage>
			,public NSUISystem::IEventListener
		{
		protected:
			NSUISystem::IEventScene * mEventScene;
			TVector<NSUISystem::IGraphicWindow*> mGraphicWindows;
			TVector<NSUISystem::IEventWindow*> mEventWindows;
		public:
			CLoginPage();
			~CLoginPage();

			// 通过 IEventListener 继承
			virtual Void onEvent(NSUISystem::IEvent * e) override;
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