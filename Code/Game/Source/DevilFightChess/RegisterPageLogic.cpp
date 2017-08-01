#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

namespace NSDevilX
{
	namespace NSFightChess
	{
		static Void onOK()
		{
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_Register);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_Login);
			page->setButtonLogic(CLoginPageLogic::buttonLogic);
			CApp::getSingleton().getGame()->stopModule("Register");
		}
	}
}

Void NSDevilX::NSFightChess::CRegisterPageLogic::buttonLogic(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e)
{
	if(control->queryInterface_IControl()->getName()=="RegisterPage/Button_Cancel")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_Register);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_Login);
			page->setButtonLogic(CLoginPageLogic::buttonLogic);
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="RegisterPage/Button_OK")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->setModuleParameter("Register","mUsername",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Register)->getGUIWindow()->getEditBox("Register/Edit_Username")->getText().toString());
			CApp::getSingleton().getGame()->setModuleParameter("Register","mPassword",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Register)->getGUIWindow()->getEditBox("Register/Edit_Password")->getText().toString());
			CApp::getSingleton().getGame()->setModuleParameter("Register","mSuccessCallback",&onOK);
			CApp::getSingleton().getGame()->startModule("Register");
			break;
		}
	}
}
