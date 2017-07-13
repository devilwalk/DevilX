#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CButton::CButton(const String & name,CControl * parent)
	:CControl(name,parent)
	,mTextControl(nullptr)
	,mBackground(nullptr)
	,mPressed(False)
{
	auto background=getGraphicScene()->createWindow(name+"/Background");
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA::sBlue);
	_attachWindow(background);
	mBackground=DEVILX_NEW CGraphicWindowTextureUtility(background);
	mTextControl=DEVILX_NEW CStaticText(name+"/TextControl",this);
	mTextControl->getLayer()->setSize(CFloat2::sOne);

	auto event_window=getEventScene()->createWindow(name);
	event_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
	event_window->queryInterface_IElement()->setSize(CFloat2::sOne);
	_attachWindow(event_window);
}

NSDevilX::NSGUISystem::CButton::~CButton()
{
	DEVILX_DELETE(mBackground);
	DEVILX_DELETE(getTextControl());
}

Void NSDevilX::NSGUISystem::CButton::setBackground(NSResourceSystem::IResource * resource)
{
	mBackground->setTexture(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::CButton::getBackground() const
{
	return mBackground->getTextureResource();
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
