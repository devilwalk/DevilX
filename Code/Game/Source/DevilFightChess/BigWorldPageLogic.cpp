#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CBigWorldPageLogic::CBigWorldPageLogic()
	:CUIPageLogic(CUIPage::EType_BigWorld)
{}

NSDevilX::NSFightChess::CBigWorldPageLogic::~CBigWorldPageLogic()
{}

Void NSDevilX::NSFightChess::CBigWorldPageLogic::onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e)
{
	if(control->queryInterface_IControl()->getName()=="BigWorld/Button_Exit")
	{
		switch(e)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
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
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("BigWorld");
			CApp::getSingleton().getGame()->startModule("Login");
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_CreateMatchServer")
	{
		switch(e)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("BigWorld");
			CApp::getSingleton().getGame()->startModule("MatchServerConfig");
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_IntranetList")
	{
		switch(e)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("BigWorld");
			break;
		}
	}
}
