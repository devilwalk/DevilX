#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CBigWorldPage::CBigWorldPage(CBigWorld * bigWorld)
	:mBigWorld(bigWorld)
	,mGUIWindow(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("BigWorld");
	CUIScript script;
	script.process(CDirectory::getApplicationDirectory()+"/Resource/BigWorld.layout",mGUIWindow,this,this);
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
	else if(control->queryInterface_IControl()->getName()=="BigWorld/Button_SinglePlayer")
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

NSDevilX::NSFightChess::CBigWorld::CBigWorld()
	:CModule("BigWorld")
	,mPage(nullptr)
	,mReturnCode(-1)
{}

NSDevilX::NSFightChess::CBigWorld::~CBigWorld()
{
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
	DEVILX_DELETE(mPage);
	mPage=nullptr;
}
