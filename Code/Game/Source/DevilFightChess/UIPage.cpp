#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CUIPage::CUIPage(EType type)
	:mType(type)
	,mPageLogic(nullptr)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("UIPage/"+CStringConverter::toString(type));
	CUIScript script;
	script.process(CApp::getSingleton().getGame()->getUIManager()->getPageResourceLocation(type),mGUIWindow);
}

NSDevilX::NSFightChess::CUIPage::~CUIPage()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

Void NSDevilX::NSFightChess::CUIPage::setPageLogic(CUIPageLogic * logic)
{
	for(UInt32 i=0;i<getGUIWindow()->getButtonCount();++i)
	{
		getGUIWindow()->getButton(i)->setEventCallback(logic);
	}
	for(UInt32 i=0;i<getGUIWindow()->getEditBoxCount();++i)
	{
		getGUIWindow()->getEditBox(i)->setEventCallback(logic);
	}
}
