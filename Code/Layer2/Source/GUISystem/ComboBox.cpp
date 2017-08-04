#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CComboBoxItem::CComboBoxItem()
{}

NSDevilX::NSGUISystem::CComboBoxItem::~CComboBoxItem()
{}

Void NSDevilX::NSGUISystem::CComboBoxItem::setControl(CCommonControl * control)
{
	mControl=control;
	if(mControl)
	{
		mControl->getTextControl()->setText(getText());
		mControl->getImageControl()->setBackground(getBackground());
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

NSDevilX::NSGUISystem::CComboBox::CComboBox(const String & name,CControl * coordParent,CControl * orderParent)
	:CControl(name,coordParent,orderParent)
	,mItemShowStart(0)
	,mEditBox(nullptr)
	,mDropList(nullptr)
	,mDropIcon(nullptr)
{
	mEditBox=DEVILX_NEW CEditBox(name+"/EditControl",this,this);
	mEditBox->getLayer()->setSize(CFloat2(0.95f,1.0f));
	mDropList=DEVILX_NEW CDropList(name+"/DropListControl",this,this);
	mDropList->getLayer()->setSize(CFloat2::sZero);
	mDropIcon=DEVILX_NEW CButton(name+"/DropIcon",this,this);
	mDropIcon->getLayer()->setPosition(CFloat2(0.95f,0.475f));
	mDropIcon->getLayer()->setSize(CFloat2(0.05f));
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
	mDropList->setSize(sizeInItems);
	if(getItemListShowSize()<sizeInItems)
	{
		for(UInt32 i=sizeInItems;i<getItemListShowSize();++i)
		{
			auto control=DEVILX_NEW CCommonControl(getLayer()->getName()+"/ItemShow/"+CStringConverter::toString(i),this,this);
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

Void NSDevilX::NSGUISystem::CComboBox::onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}

Void NSDevilX::NSGUISystem::CComboBox::onMessage(CDropList * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}
