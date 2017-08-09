#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CButton::CButton(const String & name,CControl * coordParent)
	:CControl(name,coordParent)
	,mCommonControl(nullptr)
	,mAlphaControl(nullptr)
	,mPressed(False)
{
	mCommonControl=DEVILX_NEW CCommonControl(name+"/CommonControl",this);
	mCommonControl->setOrderParent(this);
	mAlphaControl=DEVILX_NEW CImageBox(name+"/AlphaControl",this);
	mAlphaControl->setOrderParent(mCommonControl);
	mAlphaControl->setBackgroundColour(CFloatRGBA(0.0f,0.0f,1.0f,0.5f));
	mAlphaControl->setVisible(False);
}

NSDevilX::NSGUISystem::CButton::~CButton()
{
	DEVILX_DELETE(mCommonControl);
	DEVILX_DELETE(mAlphaControl);
}

Void NSDevilX::NSGUISystem::CButton::setPrepareFocus(Bool focus)
{
	mPressed=False;
	if(focus)
	{
		mAlphaControl->setVisible(True);
		ISystemImp::getSingleton().getWindow()->registerEventListener(this);
	}
	else
	{
		mAlphaControl->setVisible(False);
		ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
	}
}

Void NSDevilX::NSGUISystem::CButton::_setOrderChild(CControl * control)
{
	if(control==mCommonControl)
	{
		CControl::_setOrderChild(control);
	}
	else
	{
		assert(0);
	}
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
