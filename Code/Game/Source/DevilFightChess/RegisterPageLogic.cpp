#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CRegisterPageLogic::CRegisterPageLogic()
	:CUIPageLogic(CUIPage::EType_Register)
{}

NSDevilX::NSFightChess::CRegisterPageLogic::~CRegisterPageLogic()
{}

Void NSDevilX::NSFightChess::CRegisterPageLogic::onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e)
{
	if(control->queryInterface_IControl()->getName()=="RegisterPage/Button_Cancel")
	{
		switch(e)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_Register);
			CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_Login);
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="RegisterPage/Button_OK")
	{
		switch(e)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->setModuleParameter("Register","mUsername",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Register)->getGUIWindow()->getEditBox("Register/Edit_Username")->getText().toString());
			CApp::getSingleton().getGame()->setModuleParameter("Register","mPassword",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Register)->getGUIWindow()->getEditBox("Register/Edit_Password")->getText().toString());
			CApp::getSingleton().getGame()->startModule("Register");
			break;
		}
	}
}
