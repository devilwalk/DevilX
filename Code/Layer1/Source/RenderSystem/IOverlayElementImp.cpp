#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IOverlayElementImp::IOverlayElementImp(const String & name)
	:mName(name)
	,mPosition(CFloat2::sZero)
	,mSize(CFloat2::sZero)
	,mOrder(0)
	,mColourUnitState(nullptr)
	,mTextureUnitState(nullptr)
	,mUVOffset(CFloat2::sZero)
	,mUVScale(CFloat2::sOne)
{}

NSDevilX::NSRenderSystem::IOverlayElementImp::~IOverlayElementImp()
{}

const String & NSDevilX::NSRenderSystem::IOverlayElementImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSRenderSystem::IOverlayElementImp::setPosition(const CFloat2 & position)
{
	if(position!=getPosition())
	{
		notify(EMessage_BeginPositionChange);
		mPosition=position;
		notify(EMessage_EndPositionChange);
	}
}

const CFloat2 & NSDevilX::NSRenderSystem::IOverlayElementImp::getPosition() const
{
	// TODO: 在此处插入 return 语句
	return mPosition;
}

Void NSDevilX::NSRenderSystem::IOverlayElementImp::setSize(const CFloat2 & size)
{
	if(size!=getSize())
	{
		notify(EMessage_BeginSizeChange);
		mSize=size;
		notify(EMessage_EndSizeChange);
	}
}

const CFloat2 & NSDevilX::NSRenderSystem::IOverlayElementImp::getSize() const
{
	// TODO: 在此处插入 return 语句
	return mSize;
}

Void NSDevilX::NSRenderSystem::IOverlayElementImp::setOrder(Int32 order)
{
	if(order!=getOrder())
	{
		notify(EMessage_BeginOrderChange);
		mOrder=order;
		notify(EMessage_EndOrderChange);
	}
}

Int32 NSDevilX::NSRenderSystem::IOverlayElementImp::getOrder() const
{
	return mOrder;
}

IColourUnitState * NSDevilX::NSRenderSystem::IOverlayElementImp::getColourUnitState()
{
	if(!mColourUnitState)
	{
		notify(EMessage_BeginColourUnitStateCreate);
		mColourUnitState=DEVILX_NEW IColourUnitStateImp();
		mColourUnitState->setUserPointer(0,this);
		notify(EMessage_EndColourUnitStateCreate,mColourUnitState);
	}
	return mColourUnitState;
}

ITextureUnitState * NSDevilX::NSRenderSystem::IOverlayElementImp::getTextureUnitState()
{
	if(!mTextureUnitState)
	{
		notify(EMessage_BeginTextureUnitStateCreate);
		mTextureUnitState=DEVILX_NEW ITextureUnitStateImp();
		mTextureUnitState->setUserPointer(0,this);
		notify(EMessage_EndTextureUnitStateCreate,mTextureUnitState);
	}
	return mTextureUnitState;
}

Void NSDevilX::NSRenderSystem::IOverlayElementImp::setUVTransform(const CFloat2 & offset,const CFloat2 & scale)
{
	if((offset!=getUVOffset())||(scale!=getUVScale()))
	{
		notify(EMessage_BeginUVTransformChange);
		mUVOffset=offset;
		mUVScale=scale;
		notify(EMessage_EndUVTransformChange);
	}
}

const CFloat2 & NSDevilX::NSRenderSystem::IOverlayElementImp::getUVOffset() const
{
	// TODO: 在此处插入 return 语句
	return mUVOffset;
}

const CFloat2 & NSDevilX::NSRenderSystem::IOverlayElementImp::getUVScale() const
{
	// TODO: 在此处插入 return 语句
	return mUVScale;
}