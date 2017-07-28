#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchServerConfigPage::CMatchServerConfigPage(CMatchServerConfig * config)
	:mModule(config)
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
			CApp::getSingleton().getGame()->stopModule("MatchServerConfig");
			CApp::getSingleton().getGame()->startModule("BigWorld");
		}
		break;
		}
	}
	else if(control->queryInterface_IControl()->getName()=="MatchServerConfig/Button_Cancel")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			CApp::getSingleton().getGame()->stopModule("MatchServerConfig");
			CApp::getSingleton().getGame()->startModule("BigWorld");
			break;
		}
	}
}

Void NSDevilX::NSFightChess::CMatchServerConfigPage::onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent events)
{
	return Void();
}

NSDevilX::NSFightChess::CMatchServerConfig::CMatchServerConfig()
	:CModule("MatchServerConfig")
	,mPage(nullptr)
	,mReturnCode(-1)
{}

NSDevilX::NSFightChess::CMatchServerConfig::~CMatchServerConfig()
{
	DEVILX_DELETE(mPage);
}

Void NSDevilX::NSFightChess::CMatchServerConfig::start()
{
	mPage=DEVILX_NEW CMatchServerConfigPage(this);
}

Void NSDevilX::NSFightChess::CMatchServerConfig::update()
{
	return Void();
}

Void NSDevilX::NSFightChess::CMatchServerConfig::stop()
{
	CModule::stop();
	DEVILX_DELETE(mPage);
	mPage=nullptr;
	mReturnCode.write(-1);
}
