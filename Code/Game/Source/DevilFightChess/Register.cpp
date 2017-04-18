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

NSDevilX::NSFightChess::CRegisterPage::CRegisterPage()
	:mGUIWindow(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("RegisterPage");
	CUIScript script;
	script.process(CDirectory::getApplicationDirectory()+"/Resource/RegisterPage.layout",mGUIWindow,this,this);
}

NSDevilX::NSFightChess::CRegisterPage::~CRegisterPage()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

Void NSDevilX::NSFightChess::CRegisterPage::onEvent(NSGUISystem::IButton * control,IButtonEventCallback::EEvent events)
{
	if(control->queryInterface_IControl()->getName()=="RegisterPage/Button_Cancel")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("Register");
			CApp::getSingleton().getGame()->startModule("Login");
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="RegisterPage/Button_Register")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("Register");
			CApp::getSingleton().getGame()->startModule("Login");
			break;
		}
	}
}

Void NSDevilX::NSFightChess::CRegisterPage::onEvent(NSGUISystem::IEditBox * control,IEditBoxEventCallback::EEvent events)
{
	return Void();
}

NSDevilX::NSFightChess::CRegister::CRegister()
	:CModule("Register")
	,mPage(nullptr)
	,mReturnCode(-1)
{}

NSDevilX::NSFightChess::CRegister::~CRegister()
{
	DEVILX_DELETE(mPage);
}

Void NSDevilX::NSFightChess::CRegister::doneMT(CServer::EReturnCode code)
{
	mReturnCode.write(code);
}

Void NSDevilX::NSFightChess::CRegister::start()
{
	//CApp::getSingleton().getGame()->getServerManager()->localUserRegister("Default","123",NSInternal::registerCallback,this);
	mPage=DEVILX_NEW CRegisterPage;
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
	DEVILX_DELETE(mPage);
	mPage=nullptr;
}
