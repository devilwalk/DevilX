#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ISubEntityImp::ISubEntityImp(const String & name,IEntityImp * object)
	:mName(name)
	,mObject(object)
	,mIsRenderable(True)
	,mIsQueriable(False)
	,mQueryBuffer(nullptr)
	,mQueryBufferUsage(nullptr)
	,mGeometry(nullptr)
	,mGeometryUsage(nullptr)
	,mVisible(True)
	,mLightEnable(False)
	,mAlphaTestValue(0)
	,mTransparentEnable(False)
{
	mGeometryUsage=DEVILX_NEW IGeometryUsageImp();
}

NSDevilX::NSRenderSystem::ISubEntityImp::~ISubEntityImp()
{
	for(auto cus:mColourUnitStates)
		DEVILX_DELETE(cus);
	for(auto tus:mTextureUnitStates)
		DEVILX_DELETE(tus);
	DEVILX_DELETE(mGeometryUsage);
}

const String & NSDevilX::NSRenderSystem::ISubEntityImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IEntity * NSDevilX::NSRenderSystem::ISubEntityImp::getEntity() const
{
	return mObject;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setRenderable(Bool renderable)
{
	if(isRenderable()!=renderable)
	{
		notify(EMessage_BeginRenderableChange);
		mIsRenderable=renderable;
		notify(EMessage_EndRenderableChange);
	}
}

Bool NSDevilX::NSRenderSystem::ISubEntityImp::isRenderable() const
{
	return mIsRenderable;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setQueriable(Bool queriable)
{
	if(isQueriable()!=queriable)
	{
		notify(EMessage_BeginQueriableChange);
		mIsQueriable=queriable;
		if(queriable)
		{
			if(nullptr!=getQueryBufferUsage())
			{
				DEVILX_DELETE(mQueryBufferUsage);
				mQueryBufferUsage=nullptr;
			}
		}
		else
		{
			if(nullptr==getQueryBufferUsage())
			{
				mQueryBufferUsage=DEVILX_NEW IBufferUsageImp;
			}
		}
		notify(EMessage_EndQueriableChange);
	}
}

Bool NSDevilX::NSRenderSystem::ISubEntityImp::isQueriable() const
{
	return mIsQueriable;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setQueryBuffer(IBuffer * buffer)
{
	if(getQueryBuffer()!=buffer)
	{
		notify(EMessage_BeginQueryBufferChange);
		mQueryBuffer=static_cast<IBufferImp*>(buffer);
		notify(EMessage_EndQueryBufferChange);
	}
}

IBuffer * NSDevilX::NSRenderSystem::ISubEntityImp::getQueryBuffer() const
{
	return mQueryBuffer;
}

IBufferUsage * NSDevilX::NSRenderSystem::ISubEntityImp::getQueryBufferUsage() const
{
	return mQueryBufferUsage;
}

IGeometryUsage * NSDevilX::NSRenderSystem::ISubEntityImp::queryInterface_IGeometryUsage() const
{
	return mGeometryUsage;
}

IColourUnitStateImp * NSDevilX::NSRenderSystem::ISubEntityImp::getColourUnitState(IEnum::EEntityColourUnitStateType type) const
{
	if(static_cast<decltype(type)>(mColourUnitStates.size())>type)
		return mColourUnitStates[type];
	else
		return nullptr;
}

ITextureUnitStateImp * NSDevilX::NSRenderSystem::ISubEntityImp::getTextureUnitState(IEnum::EEntityTextureUnitStateType type) const
{
	if(static_cast<decltype(type)>(mTextureUnitStates.size())>type)
		return mTextureUnitStates[type];
	else
		return nullptr;
}

IColourUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getColourUnitState(IEnum::EEntityColourUnitStateType type)
{
	if(static_cast<decltype(type)>(mColourUnitStates.size())<=type)
		mColourUnitStates.resize(type+1);
	if(!mColourUnitStates[type])
	{
		notify(EMessage_BeginColourUnitStateCreate);
		mColourUnitStates[type]=DEVILX_NEW IColourUnitStateImp();
		notify(EMessage_EndColourUnitStateCreate,&type);
	}
	return mColourUnitStates[type];
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setLightEnable(Bool enable)
{
	if(enable!=getLightEnable())
	{
		notify(EMessage_BeginLightEnableChange);
		mLightEnable=enable;
		notify(EMessage_EndLightEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::ISubEntityImp::getLightEnable() const
{
	return mLightEnable;
}

ITextureUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getTextureUnitState(IEnum::EEntityTextureUnitStateType type)
{
	if(static_cast<decltype(type)>(mTextureUnitStates.size())<=type)
		mTextureUnitStates.resize(type+1);
	if(!mTextureUnitStates[type])
	{
		notify(EMessage_BeginTextureUnitStateCreate);
		mTextureUnitStates[type]=DEVILX_NEW ITextureUnitStateImp();
		notify(EMessage_EndTextureUnitStateCreate,&type);
	}
	return mTextureUnitStates[type];
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setAlphaTestValue(Float alpha)
{
	if(alpha!=getAlphaTestValue())
	{
		notify(EMessage_BeginAlphaTestValueChange);
		const Boolean old_enable=mAlphaTestValue>0;
		const Boolean new_enable=alpha>0;
		const Boolean enable_change=old_enable!=new_enable;
		if(enable_change)
			notify(EMessage_BeginAlphaTestEnableChange);
		mAlphaTestValue=alpha;
		if(enable_change)
			notify(EMessage_EndAlphaTestEnableChange);
		notify(EMessage_EndAlphaTestValueChange);
	}
}

Float NSDevilX::NSRenderSystem::ISubEntityImp::getAlphaTestValue() const
{
	return mAlphaTestValue;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setTransparentEnable(Bool enable)
{
	if(enable!=getTransparentEnable())
	{
		notify(EMessage_BeginTransparentEnableChange);
		mTransparentEnable=enable;
		notify(EMessage_EndTransparentEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::ISubEntityImp::getTransparentEnable() const
{
	return mTransparentEnable;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setVisible(Bool visible)
{
	if(visible!=mVisible)
	{
		CMessageNotifier::notify(EMessage_BeginVisibleChange);
		mVisible=visible;
		CMessageNotifier::notify(EMessage_EndVisibleChange);
	}
}

Bool NSDevilX::NSRenderSystem::ISubEntityImp::getVisible() const
{
	return mVisible;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setGeometry(IGeometry * geometry)
{
	if(geometry!=getGeometry())
	{
		notify(EMessage_BeginGeometryChange,static_cast<IGeometryImp*>(geometry));
		mGeometry=static_cast<IGeometryImp*>(geometry);
		notify(EMessage_EndGeometryChange);
	}
}

IGeometry * NSDevilX::NSRenderSystem::ISubEntityImp::getGeometry() const
{
	return mGeometry;
}
