#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CListItem::CListItem(UInt32 rowIndex,UInt32 columeIndex,CList * list)
	:CControl(list->getLayer()->getName()+"/Item/"+CStringConverter::toString(columeIndex)+","+CStringConverter::toString(rowIndex),list)
	,mAlphaControl(nullptr)
	,mRowIndex(rowIndex)
	,mColumeIndex(columeIndex)
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

NSDevilX::NSGUISystem::CList::CList(const String & name,CControl * coordParent)
	:CControl(name,coordParent,False)
	,mSelectRow(-1)
	,mSelectColume(-1)
{}

NSDevilX::NSGUISystem::CList::~CList()
{}

Void NSDevilX::NSGUISystem::CList::setSize(UInt32 rowSize,UInt32 columeSize)
{
	rowSize=rowSize?rowSize:1;
	columeSize=columeSize?columeSize:1;
	mItems.resize(columeSize);
	for(UInt32 colume=0;colume<getColumeSize();++colume)
	{
		auto & items=mItems[colume];
		items.resize(rowSize);
		for(UInt32 row=0;row<getRowSize();++row)
		{
			auto item=items[row];
			if(!item)
			{
				item=DEVILX_NEW CListItem(row,colume,this);
				items[row]=item;
				item->setVisible(getVisible());
				item->addListener(static_cast<TMessageReceiver<CListItem>*>(this),CListItem::EMessage_Select);
				item->setOrderParent(this);
			}
			auto const & size=_getItemSize();
			item->getLayer()->setPosition(size*CUInt2(colume,row));
			item->getLayer()->setSize(size);
		}
	}
}

Void NSDevilX::NSGUISystem::CList::setVisible(Bool visible)
{
	if(!visible)
	{
		mSelectRow=-1;
		mSelectColume=-1;
	}
	for(auto const &items:mItems)
	{
		for(auto item:items)
		{
			item->setVisible(visible);
		}
	}
	CControl::setVisible(visible);
}

Void NSDevilX::NSGUISystem::CList::_setOrderChild(CControl * control)
{
	auto is_child=false;
	for(auto const &items:mItems)
	{
		if(items.has(static_cast<CListItem*>(control)))
		{
			is_child=true;
			break;
		}
	}
	if(is_child)
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
		if((notifier->getRowIndex()!=getSelectRow())||(notifier->getColumeIndex()!=getSelectColume()))
		{
			mSelectRow=notifier->getRowIndex();
			mSelectColume=notifier->getColumeIndex();
			notify(EMessage_SelectIndexChange);
		}
		break;
	}
}
