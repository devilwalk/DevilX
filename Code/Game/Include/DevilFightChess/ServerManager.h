#pragma once
#include "Server.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CServerManager
			:public TBaseObject<CServerManager>
		{
		protected:
			CServer * mLocal;
		public:
			CServerManager();
			~CServerManager();
			Void localUserRegister(const String & name,const String & password,CServer::userRegisterCallback callback,VoidPtr userData);
			Void remoteUserRegister(const String & name,const String & password,CServer::userRegisterCallback callback,VoidPtr userData);
			Void localUserLogin(const String & name,const String & password,CServer::userLoginCallback callback,VoidPtr userData);
			Void remoteUserLogin(const String & name,const String & password,CServer::userLoginCallback callback,VoidPtr userData);
		};
	}
}