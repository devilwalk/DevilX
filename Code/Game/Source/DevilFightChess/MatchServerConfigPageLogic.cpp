#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

Void NSDevilX::NSFightChess::CMatchServerConfigPageLogic::buttonLogic(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent events)
{
	if(control->queryInterface_IControl()->getName()=="MatchServerConfig/Button_OK")
	{
		switch(events)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
		{
			auto server_name=CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_MatchServerConfig)->getGUIWindow()->getEditBox("MatchServerConfig/EditBox_Name")->getText().toString();
			if(server_name.empty())
			{
				CApp::getSingleton().getGame()->messageBox(CUTF16String(L"名称不能为空!",sizeof(L"名称不能为空!")));
				break;
			}
			auto server=CApp::getSingleton().getGame()->getMatchServerManager()->createServer(server_name);
			auto password=CApp::getSingleton().getGame()->getUIManager()->getPage(CUIPage::EType_MatchServerConfig)->getGUIWindow()->getEditBox("MatchServerConfig/EditBox_Password")->getText().toString();
			server->setPassword(password);
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_MatchServerConfig);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_BigWorld);
			page->setButtonLogic(CBigWorldPageLogic::buttonLogic);
		}
		break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="MatchServerConfig/Button_Cancel")
	{
		switch(events)
		{
		case NSGUISystem::IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->getUIManager()->destroyPage(CUIPage::EType_MatchServerConfig);
			auto page=CApp::getSingleton().getGame()->getUIManager()->createPage(CUIPage::EType_BigWorld);
			page->setButtonLogic(CBigWorldPageLogic::buttonLogic);
			break;
		}
	}
}