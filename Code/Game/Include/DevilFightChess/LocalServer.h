#pragma once
#include "Server.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CLocalServer
			:public CServer
			,public TBaseObject<CLocalServer>
		{
		protected:
			CDirectory mDatabaseDirectory;
		public:
			CLocalServer();
			~CLocalServer();

			// Í¨¹ý CServer ¼Ì³Ð
			virtual Void userRegister(const String & name,const String & password,userRegisterCallback callback,VoidPtr userData) override;
			virtual Void userLogin(const String & name,const String & password,userLoginCallback callback,VoidPtr userData) override;
		};
	}
}