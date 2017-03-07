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
	:mEventScene(nullptr)
{
	mEventScene=NSUISystem::getSystem()->createEventScene("LoginPage");
	auto background=CApp::getSingleton().getGame()->getUIManager()->getGraphicScene()->createWindow("LoginPage/Background");
	background->queryInterface_IElement()->setPosition(CFloat2(0.25f));
	background->queryInterface_IElement()->setSize(CFloat2(0.5f));
	background->setColour(CFloatRGB::sWhite);
	mGraphicWindows.push_back(background);
	CApp::getSingleton().getGame()->getUIManager()->createStaticText("LoginPage/StaticText/Username",L"ÓÃ»§Ãû:",background->queryInterface_IElement()->convertPosition(CFloat2(0.2f)),background->queryInterface_IElement()->convertSize(CFloat2(0.2f,0.05f)));
	CApp::getSingleton().getGame()->getUIManager()->createStaticText("LoginPage/StaticText/Password",L"ÃÜÂë:",background->queryInterface_IElement()->convertPosition(CFloat2(0.2f,0.25f)),background->queryInterface_IElement()->convertSize(CFloat2(0.2f,0.05f)));
}

NSDevilX::NSFightChess::CLoginPage::~CLoginPage()
{
	for(auto window:mGraphicWindows)
		CApp::getSingleton().getGame()->getUIManager()->getGraphicScene()->destroyWindow(window);
	NSUISystem::getSystem()->destroyEventScene(mEventScene);
}

Void NSDevilX::NSFightChess::CLoginPage::onEvent(NSUISystem::IEvent * e)
{
	return Void();
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
