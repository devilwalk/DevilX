#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IEditBoxImp::IEditBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_EditBox,DEVILX_NEW CEditBox(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl(),static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mTextProperty=DEVILX_NEW ITextPropertyImp();
	mTextProperty->add(static_cast<CEditBox*>(mControl->getControl())->getCommonControl()->getTextControl()->getTextProperty());
	getTextProperty()->setRowAlignMode(IEnum::ETextRowAlignMode_Left);
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
	static_cast<CEditBox*>(mControl->getControl())->getCommonControl()->getTextControl()->setText(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IEditBoxImp::getText() const
{
	// TODO: �ڴ˴����� return ���
	return static_cast<CEditBox*>(mControl->getControl())->getCommonControl()->getTextControl()->getText();
}

Void NSDevilX::NSGUISystem::IEditBoxImp::setBackground(NSResourceSystem::IResource * resource)
{
	static_cast<CEditBox*>(mControl->getControl())->getCommonControl()->getImageControl()->setBackground(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IEditBoxImp::getBackground() const
{
	return static_cast<CEditBox*>(mControl->getControl())->getCommonControl()->getImageControl()->getBackground();
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
	case CEditBox::EMessage_EndTextChange:
		if(getEventCallback())
			getEventCallback()->onEvent(this,IEditBoxEventCallback::EEvent_TextChange);
		break;
	}
}