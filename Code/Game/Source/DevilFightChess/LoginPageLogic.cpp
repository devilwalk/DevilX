#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

namespace NSDevilX
{
	namespace NSFightChess
	{
		static Void onOK()
		{
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_Login);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_BigWorld);
			page->setButtonLogic(CBigWorldPageLogic::buttonLogic);
			CApp::getSingleton().getGame()->stopModule("Login");
		}
	}
}

Void NSDevilX::NSFightChess::CLoginPageLogic::buttonLogic(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e)
{
	if(control->queryInterface_IControl()->getName()=="LoginPage/Button_Close")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			PostMessage(static_cast<HWND>(CApp::getSingleton().getWindow()->getHandle()),WM_QUIT,0,0);
#endif
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="LoginPage/Button_Register")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_Login);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_Register);
			page->setButtonLogic(CRegisterPageLogic::buttonLogic);
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="LoginPage/Button_OK")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->setModuleParameter("Login","mUsername",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Login)->getGUIWindow()->getEditBox("LoginPage/ComboBox_Username")->getText().toString());
			CApp::getSingleton().getGame()->setModuleParameter("Login","mPassword",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Login)->getGUIWindow()->getEditBox("LoginPage/Edit_Password")->getText().toString());
			CApp::getSingleton().getGame()->setModuleParameter("Login","mSuccessCallback",&onOK);
			CApp::getSingleton().getGame()->startModule("Login");
			break;
		}
	}
}
