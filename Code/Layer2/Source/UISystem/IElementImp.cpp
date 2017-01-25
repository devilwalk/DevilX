#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IElementImp::IElementImp(const String & name)
	:mName(name)
	,mPosition(CFloat3::sZero)
	,mSize(CFloat2::sZero)
{}

NSDevilX::NSUISystem::IElementImp::~IElementImp()
{}

const String & NSDevilX::NSUISystem::IElementImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSUISystem::IElementImp::setPosition(DirectX::FXMVECTOR positionVec)
{
	if(positionVec!=getPosition())
	{
		notify(EMessage_BeginPositionChange);
		mPosition=positionVec;
		notify(EMessage_EndPositionChange);
	}
}

const CFloat3 & NSDevilX::NSUISystem::IElementImp::getPosition() const
{
	// TODO: 在此处插入 return 语句
	return mPosition;
}

Void NSDevilX::NSUISystem::IElementImp::setSize(DirectX::FXMVECTOR sizeVec)
{
	if(sizeVec!=getSize())
	{
		notify(EMessage_BeginSizeChange);
		mSize=sizeVec;
		notify(EMessage_EndSizeChange);
	}
}

const CFloat2 & NSDevilX::NSUISystem::IElementImp::getSize() const
{
	// TODO: 在此处插入 return 语句
	return mSize;
}
