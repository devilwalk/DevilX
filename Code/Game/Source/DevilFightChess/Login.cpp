#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;
namespace NSDevilX
{
	namespace NSFightChess
	{
		namespace NSInternal
		{
			static Void loginCallback(CServer::EReturnCode code,VoidPtr userData)
			{
				auto login=static_cast<CLogin*>(userData);
				login->doneMT(code);
			}
		}
	}
}

NSDevilX::NSFightChess::CLogin::CLogin()
	:CModule("Login")
	,mReturnCode(-1)
{
}

NSDevilX::NSFightChess::CLogin::~CLogin()
{
	CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_Login);
}

Void NSDevilX::NSFightChess::CLogin::doneMT(CServer::EReturnCode code)
{
	mReturnCode.write(code);
}

Void NSDevilX::NSFightChess::CLogin::start()
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
	CApp::getSingleton().getGame()->getServerManager()->localUserLogin(username_any.get<String>(),password_any.get<String>(),NSInternal::loginCallback,this);
}

Void NSDevilX::NSFightChess::CLogin::update()
{
	auto return_code=mReturnCode.beginRead();
	mReturnCode.endRead();
	if(-1!=return_code)
		mReturnCode.write(-1);
	switch(return_code)
	{
	case CServer::EReturnCode_InvalidateUserName:
		MESSAGEBOX(L"用户名或密码错误!");
		break;
	case CServer::EReturnCode_Success:
		auto success_callback_any=getParameter("mSuccessCallback");
		if(success_callback_any.isValidate())
		{
			typedef Void SuccessCallbackFunc();
			auto func_ptr=success_callback_any.get<SuccessCallbackFunc*>();
			(*func_ptr)();
		}
		break;
	}
}

Void NSDevilX::NSFightChess::CLogin::stop()
{
	CModule::stop();
	mReturnCode.write(-1);
}
