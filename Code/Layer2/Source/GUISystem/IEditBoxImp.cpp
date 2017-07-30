#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IEditBoxImp::IEditBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_EditBox,DEVILX_NEW CEditBox(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->getControl()->getEventWindow()->registerListener(this,CEvent::EType_MouseMove);
	mTextProperty=DEVILX_NEW ITextPropertyImp(static_cast<CEditBox*>(mControl->getControl())->getTextControl()->getTextProperty());
	static_cast<CEditBox*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CEditBox>*>(this),CEditBox::EMessage_SetFocus);
	static_cast<CEditBox*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CEditBox>*>(this),CEditBox::EMessage_EndTextChange);
}

NSDevilX::NSGUISystem::IEditBoxImp::~IEditBoxImp()
{
	DEVILX_DELETE(mControl);
	DEVILX_DELETE(mTextProperty);
}

IControl * NSDevilX::NSGUISystem::IEditBoxImp::queryInterface_IControl() const
{
	return mControl;
}

ITextProperty * NSDevilX::NSGUISystem::IEditBoxImp::getTextProperty() const
{
	return mTextProperty;
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

Void NSDevilX::NSGUISystem::IEditBoxImp::onMessage(CEditBox * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CEditBox::EMessage_SetFocus:
		static_cast<IWindowImp*>(queryInterface_IControl()->getParentWindow())->setFocusControl(static_cast<IControlImp*>(queryInterface_IControl()));
		break;
	case CEditBox::EMessage_EndTextChange:
		if(getEventCallback())
			getEventCallback()->onEvent(this,IEditBoxEventCallback::EEvent_TextChange);
		break;
	}
}

Void NSDevilX::NSGUISystem::IEditBoxImp::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case CEvent::EType_MouseMove:
		static_cast<IWindowImp*>(queryInterface_IControl()->getParentWindow())->setPrepareFocusControl(static_cast<IControlImp*>(queryInterface_IControl()));
		break;
	}
}
