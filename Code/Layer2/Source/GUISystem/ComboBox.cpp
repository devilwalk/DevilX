#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CComboBoxItem::CComboBoxItem()
{}

NSDevilX::NSGUISystem::CComboBoxItem::~CComboBoxItem()
{}

Void NSDevilX::NSGUISystem::CComboBoxItem::setControl(CCommonControl * control)
{
	if(control!=mControl)
	{
		notify(EMessage_BeginControlChange);
		mControl=control;
		if(mControl)
		{
			mControl->getTextControl()->setText(getText());
			mControl->getImageControl()->setBackground(getBackground());
		}
		notify(EMessage_EndControlChange);
	}
}

Void NSDevilX::NSGUISystem::CComboBoxItem::setText(const CUTF8String & text)
{
	mText=text;
	if(mControl)
		mControl->getTextControl()->setText(getText());
}

Void NSDevilX::NSGUISystem::CComboBoxItem::setBackground(NSResourceSystem::IResource * res)
{
	mBackground=res;
	if(mControl)
		mControl->getImageControl()->setBackground(getBackground());
}

NSDevilX::NSGUISystem::CComboBox::CComboBox(const String & name,CControl * coordParent)
	:CControl(name,coordParent,False)
	,mItemShowStart(0)
	,mEditBox(nullptr)
	,mDropList(nullptr)
	,mDropIcon(nullptr)
{
	mEditBox=DEVILX_NEW CEditBox(name+"/EditControl",this);
	mEditBox->setOrderParent(this);
	mEditBox->getLayer()->setSize(CFloat2(0.95f,1.0f));
	mDropList=DEVILX_NEW CDropList(name+"/DropListControl",this);
	mDropList->setOrderParent(this);
	mDropList->getLayer()->setPosition(CFloat2(0.0f,1.0f));
	mDropList->getLayer()->setSize(CFloat2::sZero);
	mDropList->setVisible(False);
	mDropIcon=DEVILX_NEW CButton(name+"/DropIcon",this);
	mDropIcon->setOrderParent(this);
	mDropIcon->getLayer()->setPosition(CFloat2(0.95f,0.15f));
	mDropIcon->getLayer()->setSize(CFloat2(0.05f,0.7f));
	mDropList->addListener(static_cast<TMessageReceiver<CDropList>*>(this),CDropList::EMessage_SelectIndexChange);
	mDropIcon->addListener(static_cast<TMessageReceiver<CButton>*>(this),CButton::EMessage_Click);
}

NSDevilX::NSGUISystem::CComboBox::~CComboBox()
{
	DEVILX_DELETE(mEditBox);
	DEVILX_DELETE(mDropList);
	DEVILX_DELETE(mDropIcon);
}

Void NSDevilX::NSGUISystem::CComboBox::setText(const CUTF8String & text)
{
	mEditBox->getCommonControl()->getTextControl()->setText(text);
}

Void NSDevilX::NSGUISystem::CComboBox::setBackground(NSResourceSystem::IResource * resource)
{
	mEditBox->getCommonControl()->getImageControl()->setBackground(resource);
}

CComboBoxItem * NSDevilX::NSGUISystem::CComboBox::createItem()
{
	auto ret=DEVILX_NEW CComboBoxItem();
	if(getItemListShowSize()>mItems.size())
		ret->setControl(static_cast<CCommonControl*>(mDropList->getItem(static_cast<UInt32>(mItems.size()))->get()));
	mItems.push_back(ret);
	return ret;
}

Void NSDevilX::NSGUISystem::CComboBox::destroyItem(CComboBoxItem * item)
{
	mItems.destroy(item);
}

Void NSDevilX::NSGUISystem::CComboBox::setItemListShowSize(UInt32 sizeInItems)
{
	const auto old_size=getItemListShowSize();
	mDropList->getLayer()->setSize(CFloat2(1.0f,static_cast<Float>(sizeInItems)));
	mDropList->setSize(sizeInItems);
	if(old_size<sizeInItems)
	{
		for(UInt32 i=old_size;i<getItemListShowSize();++i)
		{
			auto control=DEVILX_NEW CCommonControl(getLayer()->getName()+"/ItemShow/"+CStringConverter::toString(i),this);
			mDropList->getItem(i)->set(control);
			if(mItems.size()>i)
			{
				mItems[i]->setControl(control);
			}
		}
	}
}

UInt32 NSDevilX::NSGUISystem::CComboBox::getItemListShowSize() const
{
	return mDropList->getSize();
}

Void NSDevilX::NSGUISystem::CComboBox::_setOrderChild(CControl * control)
{
	if((control==mEditBox)
		||(control==mDropList)
		||(control==mDropIcon)
		)
	{
		CControl::_setOrderChild(control);
	}
	else
		assert(0);
}

Void NSDevilX::NSGUISystem::CComboBox::onMessage(CEditBox * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}

Void NSDevilX::NSGUISystem::CComboBox::onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CButton::EMessage_Click:
		getDropList()->setVisible(True);
		break;
	}
}

Void NSDevilX::NSGUISystem::CComboBox::onMessage(CDropList * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CDropList::EMessage_SelectIndexChange:
		getEditControl()->getCommonControl()->getTextControl()->setText(static_cast<CCommonControl*>(notifier->getItem(notifier->getSelectIndex())->get())->getTextControl()->getText());
		notifier->setVisible(False);
		break;
	}
}
