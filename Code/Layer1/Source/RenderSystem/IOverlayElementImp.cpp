#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IOverlayElementImp::IOverlayElementImp(const String & name)
	:mName(name)
	,mEnable(True)
	,mPosition(CFloat2::sZero)
	,mSize(CFloat2::sZero)
	,mOrder(0)
	,mColourUnitState(nullptr)
	,mTextureUnitState(nullptr)
	,mScissorRectPosition(CFloat2::sZero)
	,mScissorRectSize(CFloat2::sOne)
{}

NSDevilX::NSRenderSystem::IOverlayElementImp::~IOverlayElementImp()
{
	if(static_cast<const IOverlayElementImp*>(this)->getColourUnitState())
	{
		DEVILX_DELETE(static_cast<const IOverlayElementImp*>(this)->getColourUnitState());
	}
	if(static_cast<const IOverlayElementImp*>(this)->getTextureUnitState())
	{
		DEVILX_DELETE(static_cast<const IOverlayElementImp*>(this)->getTextureUnitState());
	}
}

Void NSDevilX::NSRenderSystem::IOverlayElementImp::setEnable(Bool enable)
{
	if(enable!=getEnable())
	{
		notify(EMessage_BeginEnableChange);
		mEnable=enable;
		notify(EMessage_EndEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::IOverlayElementImp::getEnable() const
{
	return mEnable;
}

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

Void NSDevilX::NSRenderSystem::IOverlayElementImp::setUVs(const CFloat2 & uv0,const CFloat2 & uv1,const CFloat2 & uv2,const CFloat2 & uv3)
{
	if((getUVs()[0]!=uv0)
		||(getUVs()[1]!=uv1)
		||(getUVs()[2]!=uv2)
		||(getUVs()[3]!=uv3)
		)
	{
		notify(EMessage_BeginUVChange);
		mUVs[0]=uv0;
		mUVs[1]=uv1;
		mUVs[2]=uv2;
		mUVs[3]=uv3;
		notify(EMessage_EndUVChange);
	}
}

const CFloat2 * NSDevilX::NSRenderSystem::IOverlayElementImp::getUVs() const
{
	return mUVs;
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

Void NSDevilX::NSRenderSystem::IOverlayElementImp::SetScissorRect(const CFloat2 & position,const CFloat2 & size)
{
	if((position!=getScissorRectPosition())
		||(size!=getScissorRectSize()))
	{
		notify(EMessage_BeginScissorRectChange);
		mScissorRectPosition=position;
		mScissorRectSize=size;
		notify(EMessage_EndScissorRectChange);
	}
}

const CFloat2 & NSDevilX::NSRenderSystem::IOverlayElementImp::getScissorRectPosition() const
{
	// TODO: 在此处插入 return 语句
	return mScissorRectPosition;
}

const CFloat2 & NSDevilX::NSRenderSystem::IOverlayElementImp::getScissorRectSize() const
{
	// TODO: 在此处插入 return 语句
	return mScissorRectSize;
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