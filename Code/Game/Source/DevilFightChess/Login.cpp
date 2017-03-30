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

NSDevilX::NSFightChess::CLoginPage::CLoginPage()
	:mGUIWindow(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("LoginPage");
	CUIScript script;
	script.process(CDirectory::getApplicationDirectory()+"/Resource/LoginPage.layout",mGUIWindow);
}

NSDevilX::NSFightChess::CLoginPage::~CLoginPage()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

NSDevilX::NSFightChess::CLogin::CLogin()
	:CModule("Login")
	,mPage(nullptr)
	,mReturnCode(-1)
{}

NSDevilX::NSFightChess::CLogin::~CLogin()
{}

Void NSDevilX::NSFightChess::CLogin::doneMT(CServer::EReturnCode code)
{
	mReturnCode.write(code);
}

Void NSDevilX::NSFightChess::CLogin::start()
{
	//CApp::getSingleton().getGame()->getServerManager()->localUserLogin("Default","123",NSInternal::loginCallback,this);
	mPage=DEVILX_NEW CLoginPage;
}

Void NSDevilX::NSFightChess::CLogin::update()
{
	auto return_code=mReturnCode.beginRead();
	mReturnCode.endRead();
	switch(return_code)
	{
	case CServer::EReturnCode_InvalidateUserName:
		CApp::getSingleton().getGame()->stopModule(getName());
		CApp::getSingleton().getGame()->startModule("Register");
		break;
	case CServer::EReturnCode_Success:
		CApp::getSingleton().getGame()->stopModule(getName());
		break;
	}
}

Void NSDevilX::NSFightChess::CLogin::stop()
{
	DEVILX_DELETE(mPage);
	mPage=nullptr;
}
