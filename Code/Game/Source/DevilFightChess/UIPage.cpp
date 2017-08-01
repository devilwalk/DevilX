#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CUIPage::CUIPage(EType type)
	:mType(type)
	,mCallPage(EType_Unknown)
	,mButtonLogic(nullptr)
	,mEditBoxLogic(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("UIPage/"+CStringConverter::toString(type));
	CUIScript script;
	script.process(CApp::getSingleton().getGame()->getUIManager()->getPageResourceLocation(type),mGUIWindow);
	for(UInt32 i=0;i<getGUIWindow()->getButtonCount();++i)
	{
		getGUIWindow()->getButton(i)->setEventCallback(this);
	}
	for(UInt32 i=0;i<getGUIWindow()->getEditBoxCount();++i)
	{
		getGUIWindow()->getEditBox(i)->setEventCallback(this);
	}
}

NSDevilX::NSFightChess::CUIPage::~CUIPage()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

Void NSDevilX::NSFightChess::CUIPage::setButtonLogic(buttonLogic * logic)
{
	mButtonLogic=logic;
}

Void NSDevilX::NSFightChess::CUIPage::setEditBoxLogic(editBoxLogic * logic)
{
	mEditBoxLogic=logic;
}

Void NSDevilX::NSFightChess::CUIPage::setCallPage(EType type)
{
	mCallPage=type;
}

Void NSDevilX::NSFightChess::CUIPage::onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e)
{
	if(mButtonLogic)
	{
		(*mButtonLogic)(control,e);
	}
}

Void NSDevilX::NSFightChess::CUIPage::onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent e)
{
	if(mEditBoxLogic)
	{
		(*mEditBoxLogic)(control,e);
	}
}
