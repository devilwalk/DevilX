#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IElementImp::IElementImp(const String & name)
	:mName(name)
	,mPosition(CFloat2::sZero)
	,mDerivedPosition(CFloat2::sZero)
	,mSize(CFloat2::sZero)
	,mDerivedSize(CFloat2::sZero)
	,mOrder(0)
	,mDerivedOrder(0)
	,mParent(nullptr)
{}

NSDevilX::NSUISystem::IElementImp::~IElementImp()
{
	notify(EMessage_BeginDestruction);
	notify(EMessage_EndDestruction);
}

Void NSDevilX::NSUISystem::IElementImp::setParent(IElement * parent)
{
	if(parent!=getParent())
	{
		if(mParent)
		{
			mParent->removeListener(this,IElementImp::EMessage_EndDerivedOrderChange);
			mParent->removeListener(this,IElementImp::EMessage_EndDerivedPositionChange);
			mParent->removeListener(this,IElementImp::EMessage_EndDerivedSizeChange);
			mParent->removeListener(this,IElementImp::EMessage_EndDestruction);
		}
		mParent=static_cast<IElementImp*>(parent);
		_updateDerivedPosition();
		_updateDerivedSize();
		_updateDerivedOrder();
		if(mParent)
		{
			mParent->addListener(this,IElementImp::EMessage_EndDerivedOrderChange);
			mParent->addListener(this,IElementImp::EMessage_EndDerivedPositionChange);
			mParent->addListener(this,IElementImp::EMessage_EndDerivedSizeChange);
			mParent->addListener(this,IElementImp::EMessage_EndDestruction);
		}
	}
}

IElement * NSDevilX::NSUISystem::IElementImp::getParent() const
{
	return mParent;
}

const String & NSDevilX::NSUISystem::IElementImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSUISystem::IElementImp::setPosition(const CFloat2 & position)
{
	if(position!=getPosition())
	{
		mPosition=position;
		_updateDerivedPosition();
	}
}

const CFloat2 & NSDevilX::NSUISystem::IElementImp::getPosition() const
{
	// TODO: 在此处插入 return 语句
	return mPosition;
}

const CFloat2 & NSDevilX::NSUISystem::IElementImp::getDerivedPosition() const
{
	return mDerivedPosition;
}

Void NSDevilX::NSUISystem::IElementImp::setSize(const CFloat2 & size)
{
	if(size!=getSize())
	{
		mSize=size;
		_updateDerivedSize();
	}
}

const CFloat2 & NSDevilX::NSUISystem::IElementImp::getSize() const
{
	// TODO: 在此处插入 return 语句
	return mSize;
}

const CFloat2 & NSDevilX::NSUISystem::IElementImp::getDerivedSize() const
{
	return mDerivedSize;
}

Void NSDevilX::NSUISystem::IElementImp::setOrder(Int32 order)
{
	if(order!=getOrder())
	{
		mOrder=order;
		_updateDerivedOrder();
	}
}

Int32 NSDevilX::NSUISystem::IElementImp::getOrder() const
{
	return mOrder;
}

Int32 NSDevilX::NSUISystem::IElementImp::getDerivedOrder() const
{
	return mDerivedOrder;
}

CFloat2 NSDevilX::NSUISystem::IElementImp::convertSize(const CFloat2 & size,ECoord fromCoord,ECoord toCoord) const
{
	if(fromCoord==toCoord)
		return size;
	else
	{
		if((ECoord_Local==fromCoord)
			&&(ECoord_Parent==toCoord)
			)
		{
			return size*getSize();
		}
		else if((ECoord_Parent==fromCoord)
			&&(ECoord_Local==toCoord)
			)
		{
			return size/getSize();
		}
	}
	assert(0);
	return CFloat2::sZero;
}

CFloat2 NSDevilX::NSUISystem::IElementImp::convertPosition(const CFloat2 & position,ECoord fromCoord,ECoord toCoord) const
{
	if(fromCoord==toCoord)
		return position;
	else
	{
		if((ECoord_Local==fromCoord)
			&&(ECoord_Parent==toCoord)
			)
		{
			return position*getSize()+getPosition();
		}
		else if((ECoord_Parent==fromCoord)
			&&(ECoord_Local==toCoord)
			)
		{
			return (position-getPosition())/getSize();
		}
	}
	assert(0);
	return CFloat2::sZero;
}

Void NSDevilX::NSUISystem::IElementImp::_updateDerivedPosition()
{
	notify(EMessage_BeginDerivedPositionChange);
	if(mParent)
	{
		mDerivedPosition=mParent->getDerivedPosition()+getPosition()*mParent->getDerivedSize();
	}
	else
	{
		mDerivedPosition=getPosition();
	}
	notify(EMessage_EndDerivedPositionChange);
}

Void NSDevilX::NSUISystem::IElementImp::_updateDerivedSize()
{
	notify(EMessage_BeginDerivedSizeChange);
	if(mParent)
	{
		mDerivedSize=getSize()*mParent->getDerivedSize();
	}
	else
	{
		mDerivedSize=getSize();
	}
	notify(EMessage_EndDerivedSizeChange);
}

Void NSDevilX::NSUISystem::IElementImp::_updateDerivedOrder()
{
	notify(EMessage_BeginDerivedOrderChange);
	if(mParent)
	{
		mDerivedOrder=mParent->getDerivedOrder()+1;
	}
	else
	{
		mDerivedOrder=getOrder();
	}
	notify(EMessage_EndDerivedOrderChange);
}

Void NSDevilX::NSUISystem::IElementImp::onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IElementImp::EMessage_EndDerivedPositionChange:
		_updateDerivedPosition();
		break;
	case IElementImp::EMessage_EndDerivedSizeChange:
		_updateDerivedPosition();
		_updateDerivedSize();
		break;
	case IElementImp::EMessage_EndDerivedOrderChange:
		_updateDerivedOrder();
		break;
	case IElementImp::EMessage_EndDestruction:
		setParent(nullptr);
		break;
	}
}
