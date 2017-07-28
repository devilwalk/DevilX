#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;
namespace NSDevilX
{
	namespace NSFightChess
	{
		namespace NSInternal
		{
			static Void registerCallback(CServer::EReturnCode code,VoidPtr userData)
			{
				auto reg=static_cast<CRegister*>(userData);
				reg->doneMT(code);
			}
		}
	}
}

NSDevilX::NSFightChess::CRegister::CRegister()
	:CModule("Register")
	,mReturnCode(-1)
{}

NSDevilX::NSFightChess::CRegister::~CRegister()
{
}

Void NSDevilX::NSFightChess::CRegister::doneMT(CServer::EReturnCode code)
{
	mReturnCode.write(code);
}

Void NSDevilX::NSFightChess::CRegister::start()
{
	auto username_any=getParameter("mUsername");
	if(!username_any.isValidate())
	{
		MESSAGEBOX(L"用户名无效!");
	}
	auto password_any=getParameter("mPassword");
	if(!password_any.isValidate())
	{
		MESSAGEBOX(L"密码无效!");
	}
	CApp::getSingleton().getGame()->getServerManager()->localUserRegister(username_any.get<String>(),password_any.get<String>(),NSInternal::registerCallback,this);
}

Void NSDevilX::NSFightChess::CRegister::update()
{
	auto return_code=mReturnCode.beginRead();
	mReturnCode.endRead();
	switch(return_code)
	{
	case CServer::EReturnCode_Success:
		CApp::getSingleton().getGame()->stopModule(getName());
		CApp::getSingleton().getGame()->startModule("Login");
		break;
	}
}

Void NSDevilX::NSFightChess::CRegister::stop()
{
	CModule::stop();
	mReturnCode.write(-1);
}
