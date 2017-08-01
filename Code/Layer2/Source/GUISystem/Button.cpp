#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CButton::CButton(const String & name,CControl * coordParent,CControl * orderParent)
	:CControl(name,coordParent,orderParent)
	,mCommonControl(nullptr)
	,mPressed(False)
{
	mCommonControl=DEVILX_NEW CCommonControl(name+"/CommonControl",this,this);
	getCommonControl()->getImageControl()->setBackgroundColour(CFloatRGBA::sBlue);
	auto event_window=getEventScene()->createWindow(name);
	event_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
	event_window->queryInterface_IElement()->setSize(CFloat2::sOne);
	_attachWindow(event_window);
}

NSDevilX::NSGUISystem::CButton::~CButton()
{
	DEVILX_DELETE(getCommonControl());
}

Void NSDevilX::NSGUISystem::CButton::setPrepareFocus(Bool focus)
{
	mPressed=False;
	if(focus)
		ISystemImp::getSingleton().getWindow()->registerEventListener(this);
	else
		ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
}

Void NSDevilX::NSGUISystem::CButton::onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)
{
	if(EMouseButtonType_Left==buttonType)
	{
		switch(eventType)
		{
		case EMouseButtonEventType_Down:
			mPressed=True;
			notify(EMessage_Press);
			break;
		case EMouseButtonEventType_Up:
			notify(EMessage_Release);
			if(mPressed)
			{
				mPressed=False;
				notify(EMessage_Click);
			}
			break;
		}
	}
}
