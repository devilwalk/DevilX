#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IComboBoxItemImp::IComboBoxItemImp(CComboBoxItem * item,IComboBoxImp * comboBox)
	:mItem(item)
	,mComboBox(comboBox)
{
}

NSDevilX::NSGUISystem::IComboBoxItemImp::~IComboBoxItemImp()
{
}

Void NSDevilX::NSGUISystem::IComboBoxItemImp::setText(const CUTF8String & text)
{
	mItem->setText(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IComboBoxItemImp::getText() const
{
	// TODO: 在此处插入 return 语句
	return mItem->getText();
}

Void NSDevilX::NSGUISystem::IComboBoxItemImp::setBackground(NSResourceSystem::IResource * resource)
{
	mItem->setBackground(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IComboBoxItemImp::getBackground() const
{
	return mItem->getBackground();
}

NSDevilX::NSGUISystem::IComboBoxImp::IComboBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mItemTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	auto internal_control=DEVILX_NEW CComboBox(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	internal_control->setOrderParent(static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_ComboBox,internal_control,window);
	mTextProperty=DEVILX_NEW ITextPropertyImp;
	mTextProperty->add(static_cast<CComboBox*>(mControl->getControl())->getEditControl()->getCommonControl()->getTextControl()->getTextProperty());
	getTextProperty()->setRowAlignMode(IEnum::ETextRowAlignMode_Left);
	mItemTextProperty=DEVILX_NEW ITextPropertyImp;
	internal_control->addListener(this,CComboBox::EMessage_EndItemShowControlCreate);
	internal_control->addListener(this,CComboBox::EMessage_BeginItemShowControlDestroy);
}

NSDevilX::NSGUISystem::IComboBoxImp::~IComboBoxImp()
{
	DEVILX_DELETE(mControl);
	DEVILX_DELETE(mTextProperty);
	DEVILX_DELETE(mItemTextProperty);
}

IControl * NSDevilX::NSGUISystem::IComboBoxImp::queryInterface_IControl() const
{
	return mControl;
}

ITextProperty * NSDevilX::NSGUISystem::IComboBoxImp::getTextProperty() const
{
	return mTextProperty;
}

Void NSDevilX::NSGUISystem::IComboBoxImp::setText(const CUTF8String & text)
{
	static_cast<CComboBox*>(mControl->getControl())->getEditControl()->getCommonControl()->getTextControl()->setText(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IComboBoxImp::getText() const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CComboBox*>(mControl->getControl())->getEditControl()->getCommonControl()->getTextControl()->getText();
}

Void NSDevilX::NSGUISystem::IComboBoxImp::setBackground(NSResourceSystem::IResource * resource)
{
	static_cast<CComboBox*>(mControl->getControl())->getEditControl()->getCommonControl()->getImageControl()->setBackground(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IComboBoxImp::getBackground() const
{
	return static_cast<CComboBox*>(mControl->getControl())->getEditControl()->getCommonControl()->getImageControl()->getBackground();
}

IComboBoxItem * NSDevilX::NSGUISystem::IComboBoxImp::createItem()
{
	auto ret=DEVILX_NEW IComboBoxItemImp(static_cast<CComboBox*>(mControl->getControl())->createItem(),this);
	mItems.push_back(ret);
	return ret;
}

IComboBoxItem * NSDevilX::NSGUISystem::IComboBoxImp::getItem(UInt32 index) const
{
	return mItems[index];
}

Void NSDevilX::NSGUISystem::IComboBoxImp::destroyItem(IComboBoxItem * item)
{
	static_cast<CComboBox*>(mControl->getControl())->destroyItem(static_cast<IComboBoxItemImp*>(item)->getItem());
	mItems.destroy(static_cast<IComboBoxItemImp*>(item));
}

Void NSDevilX::NSGUISystem::IComboBoxImp::setItemListShowSize(UInt32 sizeInItems)
{
	static_cast<CComboBox*>(mControl->getControl())->setItemListShowSize(sizeInItems);
}

UInt32 NSDevilX::NSGUISystem::IComboBoxImp::getItemListShowSize() const
{
	return static_cast<CComboBox*>(mControl->getControl())->getItemListShowSize();
}

ITextProperty * NSDevilX::NSGUISystem::IComboBoxImp::getItemTextProperty() const
{
	return mItemTextProperty;
}

Void NSDevilX::NSGUISystem::IComboBoxImp::setEventCallback(IComboBoxEventCallback * callback)
{
	return Void();
}

IComboBoxEventCallback * NSDevilX::NSGUISystem::IComboBoxImp::getEventCallback() const
{
	return nullptr;
}

Void NSDevilX::NSGUISystem::IComboBoxImp::onMessage(CComboBox * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CComboBox::EMessage_EndItemShowControlCreate:
		mItemTextProperty->add(static_cast<CCommonControl*>(data)->getTextControl()->getTextProperty());
		break;
	case CComboBox::EMessage_BeginItemShowControlDestroy:
		mItemTextProperty->remove(static_cast<CCommonControl*>(data)->getTextControl()->getTextProperty());
		break;
	}
}
