#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IButtonImp::IButtonImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_Button,DEVILX_NEW CButton(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->getControl()->getEventWindow()->registerListener(this,CEvent::EType_MouseMove);
	mTextProperty=DEVILX_NEW ITextPropertyImp(static_cast<CButton*>(mControl->getControl())->getTextControl()->getTextProperty());
}

NSDevilX::NSGUISystem::IButtonImp::~IButtonImp()
{
	DEVILX_DELETE(mControl);
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
	// TODO: 在此处插入 return 语句
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
	Boolean old_callback_enable=mEventCallback!=nullptr;
	Boolean new_callback_enable=callback!=nullptr;
	Boolean callback_enable_change=old_callback_enable!=new_callback_enable;
	mEventCallback=callback;
	if(callback_enable_change)
	{
		if(new_callback_enable)
		{
			static_cast<CButton*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Click);
			static_cast<CButton*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Press);
			static_cast<CButton*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Release);
			ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
		}
		else
		{
			static_cast<CButton*>(mControl->getControl())->removeListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Click);
			static_cast<CButton*>(mControl->getControl())->removeListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Press);
			static_cast<CButton*>(mControl->getControl())->removeListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Release);
			ISystemImp::getSingleton().removeListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
		}
	}
}

IButtonEventCallback * NSDevilX::NSGUISystem::IButtonImp::getEventCallback() const
{
	return mEventCallback;
}

Void NSDevilX::NSGUISystem::IButtonImp::onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CButton::EMessage_Press:
		mLastEvents.push_back(IButtonEventCallback::EEvent_Press);
		break;
	case CButton::EMessage_Release:
		mLastEvents.push_back(IButtonEventCallback::EEvent_Release);
		break;
	case CButton::EMessage_Click:
		mLastEvents.push_back(IButtonEventCallback::EEvent_Click);
		break;
	}
}

Void NSDevilX::NSGUISystem::IButtonImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
	{
		auto last_events=mLastEvents;
		mLastEvents.clear();
		auto callback=getEventCallback();
		for(auto e:last_events)
		{
			callback->onEvent(this,e);
		}
	}
	break;
	}
}

Void NSDevilX::NSGUISystem::IButtonImp::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case CEvent::EType_MouseMove:
		static_cast<IWindowImp*>(queryInterface_IControl()->getParentWindow())->setPrepareFocusControl(static_cast<IControlImp*>(queryInterface_IControl()));
		break;
	}
}
