#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

Void NSDevilX::NSFightChess::CBigWorldPageLogic::buttonLogic(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e)
{
	if(control->queryInterface_IControl()->getName()=="BigWorld/Button_Exit")
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
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_Return")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_BigWorld);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_Login);
			page->setButtonLogic(CLoginPageLogic::buttonLogic);
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_CreateMatchServer")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_BigWorld);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_MatchServerConfig);
			page->setCallPage(CUIPage::EType_BigWorld);
			page->setButtonLogic(CMatchServerConfigPageLogic::buttonLogic);
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_IntranetList")
	{
		switch(e)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("BigWorld");
			break;
		}
	}
}
