#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CLoginPage
			:public TBaseObject<CLoginPage>
		{
		protected:
			NSGUISystem::IWindow * mGUIWindow;
		public:
			CLoginPage();
			~CLoginPage();
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
			// Í¨¹ý CModule ¼Ì³Ð
			virtual Void start() override;
			virtual Void update() override;
			virtual Void stop() override;
		};
	}
}