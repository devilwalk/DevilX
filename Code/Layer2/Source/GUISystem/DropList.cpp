#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CDropListItem::CDropListItem(UInt32 index,CDropList * dropList)
	:CControl(dropList->getLayer()->getName()+"/Item/"+CStringConverter::toString(index),dropList,dropList)
	,mBackgroundControl(nullptr)
	,mIndex(index)
	,mAttachedControl(nullptr)
	,mAttached(False)
{
	mBackgroundControl=DEVILX_NEW CImageBox(getLayer()->getName()+"/BackgroundControl",this,this);
	auto event_window=getEventScene()->createWindow(getLayer()->getName());
	event_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
	event_window->queryInterface_IElement()->setSize(CFloat2::sOne);
	_attachWindow(event_window);
}

NSDevilX::NSGUISystem::CDropListItem::~CDropListItem()
{
	if(mAttached)
	{
		DEVILX_DELETE(get());
	}
}

Void NSDevilX::NSGUISystem::CDropListItem::setPrepareFocus(Bool focus)
{
	if(focus)
	{
		mBackgroundControl->setBackgroundColour(CFloatRGB::sBlue);
		ISystemImp::getSingleton().getWindow()->registerEventListener(this);
	}
	else
	{
		mBackgroundControl->setBackgroundColour(CFloatRGB::sWhite);
		ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
	}
}

Void NSDevilX::NSGUISystem::CDropListItem::onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)
{
	if(EMouseButtonType_Left==buttonType)
	{
		notify(EMessage_Select);
	}
}

NSDevilX::NSGUISystem::CDropList::CDropList(const String & name,CControl * coordParent,CControl * orderParent)
	:CControl(name,coordParent,orderParent)
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
			item->addListener(this,CDropListItem::EMessage_Select);
			mItems.push_back(item);
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
