#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IPageBarImp::IPageBarImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_PageBar,DEVILX_NEW CPageBar(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->setUserPointer(0,this);
	mControl->getControl()->getEventWindow()->registerListener(this,CEvent::EType_MouseMove);
	mControl->addListener(static_cast<TMessageReceiver<IControlImp>*>(this),IControlImp::EMessage_BeginDestruction);
	mTextProperty=DEVILX_NEW ITextPropertyImp(static_cast<CStaticText*>(mControl->getControl())->getTextProperty());
}

NSDevilX::NSGUISystem::IPageBarImp::~IPageBarImp()
{
	DEVILX_DELETE(mTextProperty);
}

IControl * NSDevilX::NSGUISystem::IPageBarImp::queryInterface_IControl() const
{
	return mControl;
}

ITextProperty * NSDevilX::NSGUISystem::IPageBarImp::getTextProperty() const
{
	return mTextProperty;
}

Void NSDevilX::NSGUISystem::IPageBarImp::addPage(const CUTF8String & text)
{
	static_cast<CPageBar*>(mControl->getControl())->addItem(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IPageBarImp::getPage(UInt32 index) const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CPageBar*>(mControl->getControl())->getItem(index);
}

Void NSDevilX::NSGUISystem::IPageBarImp::removePage(UInt32 index)
{
	static_cast<CPageBar*>(mControl->getControl())->removeItem(index);
}

UInt32 NSDevilX::NSGUISystem::IPageBarImp::getActivePageIndex() const
{
	return UInt32();
}

Void NSDevilX::NSGUISystem::IPageBarImp::setEventCallback(IPageBarEventCallback * callback)
{
	mEventCallback=callback;
}

IPageBarEventCallback * NSDevilX::NSGUISystem::IPageBarImp::getEventCallback() const
{
	return mEventCallback;
}

Void NSDevilX::NSGUISystem::IPageBarImp::onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IControlImp::EMessage_BeginDestruction:
		DEVILX_DELETE(this);
		break;
	}
}

Void NSDevilX::NSGUISystem::IPageBarImp::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case CEvent::EType_MouseMove:
		static_cast<IWindowImp*>(queryInterface_IControl()->getParentWindow())->setFocusControl(static_cast<IControlImp*>(queryInterface_IControl()));
		break;
	}
}
