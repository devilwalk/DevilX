#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CDropListItem::CDropListItem(UInt32 index,CDropList * dropList)
	:CControl(dropList->getLayer()->getName()+"/Item/"+CStringConverter::toString(index),dropList)
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

NSDevilX::NSGUISystem::CDropListItem::~CDropListItem()
{
	if(mAttached)
	{
		DEVILX_DELETE(get());
	}
	DEVILX_DELETE(mAlphaControl);
}

Void NSDevilX::NSGUISystem::CDropListItem::set(CControl * control,Bool attach)
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

Void NSDevilX::NSGUISystem::CDropListItem::setVisible(Bool visible)
{
	if(get())
		get()->setVisible(visible);
	CControl::setVisible(visible);
}

Void NSDevilX::NSGUISystem::CDropListItem::setPrepareFocus(Bool focus)
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

Void NSDevilX::NSGUISystem::CDropListItem::_setOrderChild(CControl * control)
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

Void NSDevilX::NSGUISystem::CDropListItem::onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)
{
	if(EMouseButtonType_Left==buttonType)
	{
		notify(EMessage_Select);
	}
}

NSDevilX::NSGUISystem::CDropList::CDropList(const String & name,CControl * coordParent)
	:CControl(name,coordParent,False)
	,mSelectIndex(-1)
{}

NSDevilX::NSGUISystem::CDropList::~CDropList()
{}

Void NSDevilX::NSGUISystem::CDropList::setSize(UInt32 size)
{
	if(size>getSize())
	{
		for(UInt32 i=getSize();i<size;++i)
		{
			auto item=DEVILX_NEW CDropListItem(i,this);
			item->setVisible(getVisible());
			item->addListener(static_cast<TMessageReceiver<CDropListItem>*>(this),CDropListItem::EMessage_Select);
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
	for(UInt32 i=0;i<getSize();++i)
	{
		mItems[i]->getLayer()->setPosition(CFloat2(0.0f,_getItemHeight()*i));
		mItems[i]->getLayer()->setSize(CFloat2(1.0f,_getItemHeight()));
	}
}

Void NSDevilX::NSGUISystem::CDropList::setVisible(Bool visible)
{
	if(!visible)
		mSelectIndex=-1;
	for(auto item:mItems)
	{
		item->setVisible(visible);
	}
	CControl::setVisible(visible);
}

Void NSDevilX::NSGUISystem::CDropList::_setOrderChild(CControl * control)
{
	if(mItems.has(static_cast<CDropListItem*>(control)))
	{
		CControl::_setOrderChild(control);
	}
	else
		assert(0);
}

Void NSDevilX::NSGUISystem::CDropList::onMessage(CDropListItem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CDropListItem::EMessage_Select:
		if(notifier->getIndex()!=getSelectIndex())
		{
			mSelectIndex=notifier->getIndex();
			notify(EMessage_SelectIndexChange);
		}
		break;
	}
}
