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

NSDevilX::NSFightChess::CRegisterPage::CRegisterPage(CRegister * reg)
	:mRegister(reg)
	,mGUIWindow(nullptr)
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
	else if(control->queryInterface_IControl()->getName()=="RegisterPage/Button_OK")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
		{
			auto password_buf=mGUIWindow->getEditBox("RegisterPage/Edit_Password")->getText().toString();
			auto confirm_password_buf=mGUIWindow->getEditBox("RegisterPage/Edit_ConfirmPassword")->getText().toString();
			if(password_buf==confirm_password_buf)
			{
				auto username_buf=mGUIWindow->getEditBox("RegisterPage/Edit_Username")->getText().toString();
				CApp::getSingleton().getGame()->getServerManager()->localUserRegister(username_buf,password_buf,NSInternal::registerCallback,mRegister);
			}
		}
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
	mPage=DEVILX_NEW CRegisterPage(this);
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
	DEVILX_DELETE(mPage);
	mPage=nullptr;
	mReturnCode.write(-1);
}
