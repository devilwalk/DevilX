#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IButtonImp::IButtonImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_Button,DEVILX_NEW CButton(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->setUserPointer(0,this);
	mControl->getControl()->getEventWindow()->registerListener(this,CEvent::EType_MouseMove);
	mControl->addListener(static_cast<TMessageReceiver<IControlImp>*>(this),IControlImp::EMessage_BeginDestruction);
	mTextProperty=DEVILX_NEW ITextPropertyImp(static_cast<CButton*>(mControl->getControl())->getTextControl()->getTextProperty());
	static_cast<CButton*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Click);
	static_cast<CButton*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Press);
	static_cast<CButton*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Release);
}

NSDevilX::NSGUISystem::IButtonImp::~IButtonImp()
{
	DEVILX_DELETE(mTextProperty);
}

IControl * NSDevilX::NSGUISystem::IButtonImp::queryInterface_IControl() const
{
	return mControl;
}

ITextProperty * NSDevilX::NSGUISystem::IButtonImp::getTextProperty() const
{
	return mTextProperty;
}

Void NSDevilX::NSGUISystem::IButtonImp::setText(const CUTF8String & text)
{
	static_cast<CButton*>(mControl->getControl())->getTextControl()->setText(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IButtonImp::getText() const
{
	// TODO: �ڴ˴����� return ���
	return static_cast<CButton*>(mControl->getControl())->getTextControl()->getText();
}

Void NSDevilX::NSGUISystem::IButtonImp::setBackground(NSResourceSystem::IResource * resource)
{
	static_cast<CButton*>(mControl->getControl())->setBackground(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IButtonImp::getBackground() const
{
	return static_cast<CButton*>(mControl->getControl())->getBackground();
}

Void NSDevilX::NSGUISystem::IButtonImp::setEventCallback(IButtonEventCallback * callback)
{
	mEventCallback=callback;
}

IButtonEventCallback * NSDevilX::NSGUISystem::IButtonImp::getEventCallback() const
{
	return mEventCallback;
}

Void NSDevilX::NSGUISystem::IButtonImp::onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IControlImp::EMessage_BeginDestruction:
		DEVILX_DELETE(this);
		break;
	}
}

Void NSDevilX::NSGUISystem::IButtonImp::onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CButton::EMessage_Press:
		if(getEventCallback())
			getEventCallback()->onEvent(this,IButtonEventCallback::EEvent_Press);
		break;
	case CButton::EMessage_Release:
		if(getEventCallback())
			getEventCallback()->onEvent(this,IButtonEventCallback::EEvent_Release);
		break;
	case CButton::EMessage_Click:
		if(getEventCallback())
			getEventCallback()->onEvent(this,IButtonEventCallback::EEvent_Click);
		break;
	}
}

Void NSDevilX::NSGUISystem::IButtonImp::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case CEvent::EType_MouseMove:
		static_cast<IWindowImp*>(queryInterface_IControl()->getParentWindow())->setFocusControl(static_cast<IControlImp*>(queryInterface_IControl()));
		break;
	}
}