#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IMaterialImp::IMaterialImp(IRenderableImp * renderable)
	:mRenderable(renderable)
	,mLightEnable(False)
	,mAlphaTestValue(0)
	,mTransparentEnable(False)
{
}

NSDevilX::NSRenderSystem::IMaterialImp::~IMaterialImp()
{
	for(auto cus:mColourUnitStates)
		DEVILX_DELETE(cus);
}

IColourUnitStateImp * NSDevilX::NSRenderSystem::IMaterialImp::getColourUnitState(IEnum::EColourUnitStateType type) const
{
	if(static_cast<decltype(type)>(mColourUnitStates.size())>type)
		return mColourUnitStates[type];
	else
		return nullptr;
}

ITextureUnitStateImp * NSDevilX::NSRenderSystem::IMaterialImp::getTextureUnitState(IEnum::ETextureUnitStateType type) const
{
	if(static_cast<decltype(type)>(mTextureUnitStates.size())>type)
		return mTextureUnitStates[type];
	else
		return nullptr;
}

IColourUnitState * NSDevilX::NSRenderSystem::IMaterialImp::getColourUnitState(IEnum::EColourUnitStateType type)
{
	if(static_cast<decltype(type)>(mColourUnitStates.size())<=type)
		mColourUnitStates.resize(type+1);
	if(!mColourUnitStates[type])
	{
		notify(EMessage_BeginColourUnitStateCreate);
		mColourUnitStates[type]=DEVILX_NEW IColourUnitStateImp(type,this);
		notify(EMessage_EndColourUnitStateCreate,mColourUnitStates[type]);
	}
	return mColourUnitStates[type];
}

Void NSDevilX::NSRenderSystem::IMaterialImp::setLightEnable(Bool enable)
{
	if(enable!=getLightEnable())
	{
		notify(EMessage_BeginLightEnableChange);
		mLightEnable=enable;
		notify(EMessage_EndLightEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::IMaterialImp::getLightEnable() const
{
	return mLightEnable;
}

ITextureUnitState * NSDevilX::NSRenderSystem::IMaterialImp::getTextureUnitState(IEnum::ETextureUnitStateType type)
{
	if(static_cast<decltype(type)>(mTextureUnitStates.size())<=type)
		mTextureUnitStates.resize(type+1);
	if(!mTextureUnitStates[type])
	{
		notify(EMessage_BeginTextureUnitStateCreate);
		mTextureUnitStates[type]=DEVILX_NEW ITextureUnitStateImp(type,this);
		notify(EMessage_EndTextureUnitStateCreate,mTextureUnitStates[type]);
	}
	return mTextureUnitStates[type];
}

Void NSDevilX::NSRenderSystem::IMaterialImp::setAlphaTestValue(Float alpha)
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

Float NSDevilX::NSRenderSystem::IMaterialImp::getAlphaTestValue() const
{
	return mAlphaTestValue;
}

Void NSDevilX::NSRenderSystem::IMaterialImp::setTransparentEnable(Bool enable)
{
	if(enable!=getTransparentEnable())
	{
		notify(EMessage_BeginTransparentEnableChange);
		mTransparentEnable=enable;
		notify(EMessage_EndTransparentEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::IMaterialImp::getTransparentEnable() const
{
	return mTransparentEnable;
}
