#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IElementImp::IElementImp(const String & name)
	:mName(name)
	,mPosition(CFloat2::sZero)
	,mSize(CFloat2::sZero)
	,mOrder(0)
{}

NSDevilX::NSUISystem::IElementImp::~IElementImp()
{}

const String & NSDevilX::NSUISystem::IElementImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSUISystem::IElementImp::setPosition(const CFloat2 & position)
{
	if(position!=getPosition())
	{
		notify(EMessage_BeginPositionChange);
		mPosition=position;
		notify(EMessage_EndPositionChange);
	}
}

const CFloat2 & NSDevilX::NSUISystem::IElementImp::getPosition() const
{
	// TODO: 在此处插入 return 语句
	return mPosition;
}

Void NSDevilX::NSUISystem::IElementImp::setSize(const CFloat2 & size)
{
	if(size!=getSize())
	{
		notify(EMessage_BeginSizeChange);
		mSize=size;
		notify(EMessage_EndSizeChange);
	}
}

const CFloat2 & NSDevilX::NSUISystem::IElementImp::getSize() const
{
	// TODO: 在此处插入 return 语句
	return mSize;
}

Void NSDevilX::NSUISystem::IElementImp::setOrder(Int32 order)
{
	if(order!=getOrder())
	{
		notify(EMessage_BeginOrderChange);
		mOrder=order;
		notify(EMessage_EndOrderChange);
	}
}

Int32 NSDevilX::NSUISystem::IElementImp::getOrder() const
{
	return mOrder;
}

CFloat2 NSDevilX::NSUISystem::IElementImp::convertSize(const CFloat2 & relativeSize) const
{
	return relativeSize*getSize();
}

CFloat2 NSDevilX::NSUISystem::IElementImp::convertPosition(const CFloat2 & relativePosition) const
{
	return relativePosition*getSize()+getPosition();
}
