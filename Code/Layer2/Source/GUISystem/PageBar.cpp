#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CPageBar::CPageBar(const String & name,CControl * parent)
	:CControl(name,parent)
	,mTextProperty(nullptr)
	,mNextItemName(0)
	,mFocus(nullptr)
{
	auto background=getGraphicScene()->createWindow(name+"/Background");
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA::sBlue);
	_attachWindow(background);

	auto event_window=getEventScene()->createWindow(name);
	event_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
	event_window->queryInterface_IElement()->setSize(CFloat2::sOne);
	_attachWindow(event_window);

	mTextProperty=DEVILX_NEW CTextProperty;
	getTextProperty()->addListener(this,CTextProperty::EMessage_AddDirtyFlag);
}

NSDevilX::NSGUISystem::CPageBar::~CPageBar()
{
	DEVILX_DELETE(getTextProperty());
}

Void NSDevilX::NSGUISystem::CPageBar::setPrepareFocusControl(CPageBarItem * item)
{
	if(item!=mFocus)
	{
		if(mFocus)
			mFocus->setPrepareFocus(False);
		mFocus=item;
		if(mFocus)
			mFocus->setPrepareFocus(True);
		_updateItems();
	}
}

Void NSDevilX::NSGUISystem::CPageBar::addItem(const CUTF8String & text)
{
	auto item=DEVILX_NEW CPageBarItem(this->getLayer()->getName()+"/"+CStringConverter::toString(mNextItemName++),this);
	item->getTextControl()->getTextProperty()->copyFrom(getTextProperty());
	item->getTextControl()->setText(text);
	mItems.push_back(item);
	setPrepareFocusControl(item);
}

const CUTF8String & NSDevilX::NSGUISystem::CPageBar::getItem(UInt32 index) const
{
	// TODO: 在此处插入 return 语句
	return mItems[index]->getTextControl()->getText();
}

Void NSDevilX::NSGUISystem::CPageBar::removeItem(UInt32 index)
{
	auto item=mItems[index];
	if(item==mFocus)
	{
		mFocus=nullptr;
	}
	mItems.destroy(item);
	_updateItems();
}

Void NSDevilX::NSGUISystem::CPageBar::_updateItems()
{
	UInt32 length=0;
	for(auto item:mItems)
	{
	}
}

Void NSDevilX::NSGUISystem::CPageBar::onMessage(CTextProperty * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CTextProperty::EMessage_AddDirtyFlag:
		for(auto item:mItems)
		{
			item->getTextControl()->getTextProperty()->copyFrom(getTextProperty());
		}
		break;
	}
}
