#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CServerManager::CServerManager()
	:mLocal(nullptr)
{
	mLocal=DEVILX_NEW CLocalServer;
}

NSDevilX::NSFightChess::CServerManager::~CServerManager()
{
	DEVILX_DELETE(mLocal);
}

Void NSDevilX::NSFightChess::CServerManager::localUserRegister(const String & name,const String & password,CServer::userRegisterCallback callback,VoidPtr userData)
{
	mLocal->userRegister(name,password,callback,userData);
}

Void NSDevilX::NSFightChess::CServerManager::remoteUserRegister(const String & name,const String & password,CServer::userRegisterCallback callback,VoidPtr userData)
{
}

Void NSDevilX::NSFightChess::CServerManager::localUserLogin(const String & name,const String & password,CServer::userLoginCallback callback,VoidPtr userData)
{
	mLocal->userLogin(name,password,callback,userData);
}

Void NSDevilX::NSFightChess::CServerManager::remoteUserLogin(const String & name,const String & password,CServer::userLoginCallback callback,VoidPtr userData)
{
	return Void();
}
