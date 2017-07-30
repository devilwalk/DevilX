#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMessageBox::CMessageBox(const CUTF8String & message)
{
	mGUIWindow=CApp::getSingleton().getGame()->getGUIScene()->createWindow("MessageBox",True);
	CUIScript script;
	script.process(CDirectory::getApplicationDirectory()+"/Resource/MessageBox.layout",mGUIWindow);
	mGUIWindow->getStaticText("MessageBox/StaticText_Message")->setText(message);
	for(UInt32 i=0;i<mGUIWindow->getButtonCount();++i)
		mGUIWindow->getButton(i)->setEventCallback(this);
}

NSDevilX::NSFightChess::CMessageBox::~CMessageBox()
{
	CApp::getSingleton().getGame()->getGUIScene()->destroyWindow(mGUIWindow);
}

Void NSDevilX::NSFightChess::CMessageBox::onEvent(NSGUISystem::IButton * control,EEvent events)
{
	if(control->queryInterface_IControl()->getName()=="MessageBox/Button_OK")
	{
		switch(events)
		{
		case IButtonEventCallback::EEvent::EEvent_Click:
			DEVILX_DELETE(this);
			break;
		}
	}
}
