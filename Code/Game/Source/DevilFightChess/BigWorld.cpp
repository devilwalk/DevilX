#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CBigWorldPage::CBigWorldPage(CBigWorld * bigWorld)
	:mBigWorld(bigWorld)
	,mGUIWindow(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("BigWorld");
	CUIScript script;
	script.process(CDirectory::getApplicationDirectory()+"/Resource/BigWorldPage.layout",mGUIWindow,this,this);
}

NSDevilX::NSFightChess::CBigWorldPage::~CBigWorldPage()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

Void NSDevilX::NSFightChess::CBigWorldPage::onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent events)
{
	if(control->queryInterface_IControl()->getName()=="BigWorld/Button_Exit")
	{
		switch(events)
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
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("BigWorld");
			CApp::getSingleton().getGame()->startModule("Login");
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_CreateMatchServer")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("BigWorld");
			CApp::getSingleton().getGame()->startModule("MatchServerConfig");
			break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_IntranetList")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("BigWorld");
			break;
		}
	}
}

Void NSDevilX::NSFightChess::CBigWorldPage::onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent events)
{
	return Void();
}

NSDevilX::NSFightChess::CMatchServerConfigPage::CMatchServerConfigPage(CBigWorld * bigWorld)
	:mModule(bigWorld)
	,mGUIWindow(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("MatchServerConfig");
	CUIScript script;
	script.process(CDirectory::getApplicationDirectory()+"/Resource/MatchServerConfigPage.layout",mGUIWindow,this,this);
}

NSDevilX::NSFightChess::CMatchServerConfigPage::~CMatchServerConfigPage()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

Void NSDevilX::NSFightChess::CMatchServerConfigPage::onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent events)
{
	if(control->queryInterface_IControl()->getName()=="MatchServerConfig/Button_OK")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
		{
			auto server_name=mGUIWindow->getEditBox("MatchServerConfig/EditBox_Name")->getText().toString();
			if(server_name.empty())
			{
				CApp::getSingleton().getGame()->messageBox(CUTF16String(L"名称不能为空!",sizeof(L"名称不能为空!")));
				break;
			}
			auto server=CApp::getSingleton().getGame()->getMatchServerManager()->createServer(server_name);
			auto password=mGUIWindow->getEditBox("MatchServerConfig/EditBox_Password")->getText().toString();
			server->setPassword(password);
		}
		break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="MatchServerConfig/Button_Cancel")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			break;
		}
	}
}

Void NSDevilX::NSFightChess::CMatchServerConfigPage::onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent events)
{
	return Void();
}

NSDevilX::NSFightChess::CBigWorld::CBigWorld()
	:CModule("BigWorld")
	,mPage(nullptr)
	,mMatchServerConfigPage(nullptr)
	,mReturnCode(-1)
{}

NSDevilX::NSFightChess::CBigWorld::~CBigWorld()
{
	DEVILX_DELETE(mMatchServerConfigPage);
	DEVILX_DELETE(mPage);
}

Void NSDevilX::NSFightChess::CBigWorld::start()
{
	mPage=DEVILX_NEW CBigWorldPage(this);
}

Void NSDevilX::NSFightChess::CBigWorld::update()
{
	return Void();
}

Void NSDevilX::NSFightChess::CBigWorld::stop()
{
	CModule::stop();
	DEVILX_DELETE(mPage);
	mPage=nullptr;
	mReturnCode.write(-1);
}
