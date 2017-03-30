#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IEditBoxImp::IEditBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mEventCallback(nullptr)
{
	mControl=DEVILX_NEW IControlImp(DEVILX_NEW CEditBox(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->getControl()->getEventWindow()->registerListener(this,IWindowImp::SEvent::EType_ControlFocus);
	mControl->addListener(static_cast<TMessageReceiver<IControlImp>*>(this),IControlImp::EMessage_BeginDestruction);
	static_cast<CEditBox*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CEditBox>*>(this),CEditBox::EMessage_EndTextChange);
}

NSDevilX::NSGUISystem::IEditBoxImp::~IEditBoxImp()
{
}

IControl * NSDevilX::NSGUISystem::IEditBoxImp::queryInterface_IControl() const
{
	return mControl;
}

Void NSDevilX::NSGUISystem::IEditBoxImp::setFontResource(NSResourceSystem::IResource * resource)
{
	static_cast<CEditBox*>(mControl->getControl())->getTextControl()->setFontResource(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IEditBoxImp::getFontResource() const
{
	return static_cast<CEditBox*>(mControl->getControl())->getTextControl()->getFontResource();
}

Void NSDevilX::NSGUISystem::IEditBoxImp::setText(const CUTF8String & text)
{
	static_cast<CEditBox*>(mControl->getControl())->getTextControl()->setText(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IEditBoxImp::getText() const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CEditBox*>(mControl->getControl())->getTextControl()->getText();
}

Void NSDevilX::NSGUISystem::IEditBoxImp::setTextColour(const CColour & colour)
{
	static_cast<CEditBox*>(mControl->getControl())->getTextControl()->setTextColour(colour);
}

const CColour & NSDevilX::NSGUISystem::IEditBoxImp::getTextColour() const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CEditBox*>(mControl->getControl())->getTextControl()->getTextColour();
}

Void NSDevilX::NSGUISystem::IEditBoxImp::setBackground(NSResourceSystem::IResource * resource)
{
	static_cast<CEditBox*>(mControl->getControl())->setBackground(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IEditBoxImp::getBackground() const
{
	return static_cast<CEditBox*>(mControl->getControl())->getBackground();
}

Void NSDevilX::NSGUISystem::IEditBoxImp::setEventCallback(IEditBoxEventCallback * callback)
{
	mEventCallback=callback;
}

IEditBoxEventCallback * NSDevilX::NSGUISystem::IEditBoxImp::getEventCallback() const
{
	return mEventCallback;
}

Void NSDevilX::NSGUISystem::IEditBoxImp::onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IControlImp::EMessage_BeginDestruction:
		DEVILX_DELETE(this);
		break;
	}
}

Void NSDevilX::NSGUISystem::IEditBoxImp::onMessage(CEditBox * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CEditBox::EMessage_EndTextChange:
		if(getEventCallback())
			getEventCallback()->onEvent(IEditBoxEventCallback::EEvent_TextChange);
		break;
	}
}

Void NSDevilX::NSGUISystem::IEditBoxImp::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case IWindowImp::SEvent::EType_ControlFocus:
		static_cast<IWindowImp*>(queryInterface_IControl()->getParentWindow())->setFocusControl(static_cast<IControlImp*>(queryInterface_IControl()));
		break;
	}
}
