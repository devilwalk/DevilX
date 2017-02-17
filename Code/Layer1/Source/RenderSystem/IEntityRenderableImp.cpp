#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IEntityRenderableImp::IEntityRenderableImp(const String & name,IEntityImp * object)
	:mName(name)
	,mObject(object)
	,mGeometry(nullptr)
	,mGeometryUsage(nullptr)
	,mVisible(True)
	,mLightEnable(False)
	,mAlphaTestValue(0)
	,mTransparentEnable(False)
{
	mGeometryUsage=DEVILX_NEW IGeometryUsageImp();
}

NSDevilX::NSRenderSystem::IEntityRenderableImp::~IEntityRenderableImp()
{
	for(auto cus:mColourUnitStates)
		DEVILX_DELETE(cus);
	for(auto tus:mTextureUnitStates)
		DEVILX_DELETE(tus);
	DEVILX_DELETE(mGeometryUsage);
}

const String & NSDevilX::NSRenderSystem::IEntityRenderableImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IEntity * NSDevilX::NSRenderSystem::IEntityRenderableImp::getEntity() const
{
	return mObject;
}

IGeometryUsage * NSDevilX::NSRenderSystem::IEntityRenderableImp::queryInterface_IGeometryUsage() const
{
	return mGeometryUsage;
}

IColourUnitStateImp * NSDevilX::NSRenderSystem::IEntityRenderableImp::getColourUnitState(IEnum::EEntityColourUnitStateType type) const
{
	if(static_cast<decltype(type)>(mColourUnitStates.size())>type)
		return mColourUnitStates[type];
	else
		return nullptr;
}

ITextureUnitStateImp * NSDevilX::NSRenderSystem::IEntityRenderableImp::getTextureUnitState(IEnum::EEntityTextureUnitStateType type) const
{
	if(static_cast<decltype(type)>(mTextureUnitStates.size())>type)
		return mTextureUnitStates[type];
	else
		return nullptr;
}

IColourUnitState * NSDevilX::NSRenderSystem::IEntityRenderableImp::getColourUnitState(IEnum::EEntityColourUnitStateType type)
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

Void NSDevilX::NSRenderSystem::IEntityRenderableImp::setLightEnable(Bool enable)
{
	if(enable!=getLightEnable())
	{
		notify(EMessage_BeginLightEnableChange);
		mLightEnable=enable;
		notify(EMessage_EndLightEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::IEntityRenderableImp::getLightEnable() const
{
	return mLightEnable;
}

ITextureUnitState * NSDevilX::NSRenderSystem::IEntityRenderableImp::getTextureUnitState(IEnum::EEntityTextureUnitStateType type)
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

Void NSDevilX::NSRenderSystem::IEntityRenderableImp::setAlphaTestValue(Float alpha)
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

Float NSDevilX::NSRenderSystem::IEntityRenderableImp::getAlphaTestValue() const
{
	return mAlphaTestValue;
}

Void NSDevilX::NSRenderSystem::IEntityRenderableImp::setTransparentEnable(Bool enable)
{
	if(enable!=getTransparentEnable())
	{
		notify(EMessage_BeginTransparentEnableChange);
		mTransparentEnable=enable;
		notify(EMessage_EndTransparentEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::IEntityRenderableImp::getTransparentEnable() const
{
	return mTransparentEnable;
}

Void NSDevilX::NSRenderSystem::IEntityRenderableImp::setVisible(Bool visible)
{
	if(visible!=mVisible)
	{
		CMessageNotifier::notify(EMessage_BeginVisibleChange);
		mVisible=visible;
		CMessageNotifier::notify(EMessage_EndVisibleChange);
	}
}

Bool NSDevilX::NSRenderSystem::IEntityRenderableImp::getVisible() const
{
	return mVisible;
}

Void NSDevilX::NSRenderSystem::IEntityRenderableImp::setGeometry(IGeometry * geometry)
{
	if(geometry!=getGeometry())
	{
		notify(EMessage_BeginGeometryChange,static_cast<IGeometryImp*>(geometry));
		mGeometry=static_cast<IGeometryImp*>(geometry);
		notify(EMessage_EndGeometryChange);
	}
}

IGeometry * NSDevilX::NSRenderSystem::IEntityRenderableImp::getGeometry() const
{
	return mGeometry;
}
