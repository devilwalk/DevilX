#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CLoginPageLogic::CLoginPageLogic()
	:CUIPageLogic(CUIPage::EType_Login)
{}

NSDevilX::NSFightChess::CLoginPageLogic::~CLoginPageLogic()
{}

Void NSDevilX::NSFightChess::CLoginPageLogic::onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e)
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
			CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_Register);
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="LoginPage/Button_OK")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->setModuleParameter("Login","mUsername",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Login)->getGUIWindow()->getEditBox("LoginPage/Edit_Username")->getText().toString());
			CApp::getSingleton().getGame()->setModuleParameter("Login","mPassword",CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_Login)->getGUIWindow()->getEditBox("LoginPage/Edit_Password")->getText().toString());
			CApp::getSingleton().getGame()->startModule("Login");
			break;
		}
	}
}
