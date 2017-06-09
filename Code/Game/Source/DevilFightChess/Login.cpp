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

NSDevilX::NSFightChess::CLoginPage::CLoginPage(CLogin * login)
	:mLogin(login)
	,mGUIWindow(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("LoginPage");
	CUIScript script;
	script.process(CDirectory::getApplicationDirectory()+"/Resource/LoginPage.layout",mGUIWindow,this,this);
}

NSDevilX::NSFightChess::CLoginPage::~CLoginPage()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

Void NSDevilX::NSFightChess::CLoginPage::onEvent(NSGUISystem::IButton * control,IButtonEventCallback::EEvent events)
{
	if(control->queryInterface_IControl()->getName()=="LoginPage/Button_Close")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			PostMessage(static_cast<HWND>(CApp::getSingleton().getWindow()->getHandle()),WM_QUIT,0,0);
#endif
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="LoginPage/Button_Register")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("Login");
			CApp::getSingleton().getGame()->startModule("Register");
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="LoginPage/Button_OK")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			mLogin->login(mGUIWindow->getEditBox("LoginPage/Edit_Username")->getText().toString(),mGUIWindow->getEditBox("LoginPage/Edit_Password")->getText().toString());
			break;
		}
	}
}

Void NSDevilX::NSFightChess::CLoginPage::onEvent(NSGUISystem::IEditBox * control,IEditBoxEventCallback::EEvent events)
{
	return Void();
}

NSDevilX::NSFightChess::CLogin::CLogin()
	:CModule("Login")
	,mPage(nullptr)
	,mReturnCode(-1)
{}

NSDevilX::NSFightChess::CLogin::~CLogin()
{
	DEVILX_DELETE(mPage);
}

Void NSDevilX::NSFightChess::CLogin::login(const String & username,const String & password)
{
	CApp::getSingleton().getGame()->getServerManager()->localUserLogin(username,password,NSInternal::loginCallback,this);
}

Void NSDevilX::NSFightChess::CLogin::doneMT(CServer::EReturnCode code)
{
	mReturnCode.write(code);
}

Void NSDevilX::NSFightChess::CLogin::start()
{
	mPage=DEVILX_NEW CLoginPage(this);
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
		CApp::getSingleton().getGame()->messageBox(CUTF8String(CUTF16String(L"用户名或密码错误",sizeof(L"用户名或密码错误"))));
		break;
	case CServer::EReturnCode_Success:
		CApp::getSingleton().getGame()->stopModule(getName());
		CApp::getSingleton().getGame()->startModule("BigWorld");
		break;
	}
}

Void NSDevilX::NSFightChess::CLogin::stop()
{
	DEVILX_DELETE(mPage);
	mPage=nullptr;
}
