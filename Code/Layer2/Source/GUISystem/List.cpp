#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CListItem::CListItem(UInt32 index,CList * list)
	:CControl(list->getLayer()->getName()+"/Item/"+CStringConverter::toString(index),list)
	,mAlphaControl(nullptr)
	,mIndex(index)
	,mAttachedControl(nullptr)
	,mAttached(False)
{
	mAlphaControl=DEVILX_NEW CImageBox(getLayer()->getName()+"/AlphaControl",this);
	mAlphaControl->setOrderParent(this);
	mAlphaControl->setBackgroundColour(CFloatRGBA(0.0f,0.0f,1.0f,0.5f));
	mAlphaControl->setVisible(False);
}

NSDevilX::NSGUISystem::CListItem::~CListItem()
{
	if(mAttached)
	{
		DEVILX_DELETE(get());
	}
	DEVILX_DELETE(mAlphaControl);
}

Void NSDevilX::NSGUISystem::CListItem::set(CControl * control,Bool attach)
{
	if(get())
	{
		mAlphaControl->setOrderParent(this);
		get()->setCoordParent(nullptr);
		get()->setOrderParent(nullptr);
	}
	mAttachedControl=control;
	mAttached=attach;
	if(get())
	{
		mAlphaControl->setOrderParent(get());
		get()->setCoordParent(this);
		get()->setOrderParent(this);
		get()->setVisible(getVisible());
	}
}

Void NSDevilX::NSGUISystem::CListItem::setVisible(Bool visible)
{
	if(get())
		get()->setVisible(visible);
	CControl::setVisible(visible);
}

Void NSDevilX::NSGUISystem::CListItem::setPrepareFocus(Bool focus)
{
	if(focus)
	{
		mAlphaControl->setVisible(True);
		ISystemImp::getSingleton().getWindow()->registerEventListener(this);
	}
	else
	{
		mAlphaControl->setVisible(False);
		ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
	}
}

Void NSDevilX::NSGUISystem::CListItem::_setOrderChild(CControl * control)
{
	if((control==mAlphaControl)||(control==get()))
	{
		CControl::_setOrderChild(control);
	}
	else
	{
		assert(0);
	}
}

Void NSDevilX::NSGUISystem::CListItem::onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)
{
	if(EMouseButtonType_Left==buttonType)
	{
		notify(EMessage_Select);
	}
}

NSDevilX::NSGUISystem::CList::CList(const String & name,CControl * coordParent,EType type)
	:CControl(name,coordParent,False)
	,mType(type)
	,mSelectIndex(-1)
{}

NSDevilX::NSGUISystem::CList::~CList()
{}

Void NSDevilX::NSGUISystem::CList::setSize(UInt32 size)
{
	if(size>getSize())
	{
		for(UInt32 i=getSize();i<size;++i)
		{
			auto item=DEVILX_NEW CListItem(i,this);
			item->setVisible(getVisible());
			item->addListener(static_cast<TMessageReceiver<CListItem>*>(this),CListItem::EMessage_Select);
			mItems.push_back(item);
			item->setOrderParent(this);
		}
	}
	else if(size<getSize())
	{
		while(size<getSize())
		{
			mItems.destroy(getItem(getSize()-1));
		}
	}
	switch(mType)
	{
	case EType_Row:
		for(UInt32 i=0;i<getSize();++i)
		{
			mItems[i]->getLayer()->setPosition(CFloat2(_getItemSize()*i,0.0f));
			mItems[i]->getLayer()->setSize(CFloat2(_getItemSize(),1.0f));
		}
		break;
	case EType_Colume:
		for(UInt32 i=0;i<getSize();++i)
		{
			mItems[i]->getLayer()->setPosition(CFloat2(0.0f,_getItemSize()*i));
			mItems[i]->getLayer()->setSize(CFloat2(1.0f,_getItemSize()));
		}
		break;
	}
}

Void NSDevilX::NSGUISystem::CList::setVisible(Bool visible)
{
	if(!visible)
		mSelectIndex=-1;
	for(auto item:mItems)
	{
		item->setVisible(visible);
	}
	CControl::setVisible(visible);
}

Void NSDevilX::NSGUISystem::CList::_setOrderChild(CControl * control)
{
	if(mItems.has(static_cast<CListItem*>(control)))
	{
		CControl::_setOrderChild(control);
	}
	else
		assert(0);
}

Void NSDevilX::NSGUISystem::CList::onMessage(CListItem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CListItem::EMessage_Select:
		if(notifier->getIndex()!=getSelectIndex())
		{
			mSelectIndex=notifier->getIndex();
			notify(EMessage_SelectIndexChange);
		}
		break;
	}
}
