#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IPageBarImp::IPageBarImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	auto internal_control=DEVILX_NEW CPageBar(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	internal_control->setOrderParent(static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_PageBar,internal_control,window);

	mTextProperty=DEVILX_NEW ITextPropertyImp();
	mTextProperty->add(static_cast<CPageBar*>(mControl->getControl())->getTextProperty());
}

NSDevilX::NSGUISystem::IPageBarImp::~IPageBarImp()
{
	DEVILX_DELETE(mControl);
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