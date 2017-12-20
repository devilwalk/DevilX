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
	,mAmbientModel(IEnum::EMaterialAmbientModel_None)
	,mDiffuseModel(IEnum::EMaterialDiffuseModel_None)
	,mSpecularModel(IEnum::EMaterialSpecularModel_None)
	,mAlphaColour(nullptr)
	,mDiffuseColour(nullptr)
	,mSpecularColour(nullptr)
	,mEmissiveColour(nullptr)
	,mDiffuseTexture(nullptr)
	,mSpecularTexture(nullptr)
	,mNormalTexture(nullptr)
	,mMetallicValue(nullptr)
	,mRoughnessValue(nullptr)
	,mSpecularPowerValue(nullptr)
	,mAlphaTestValue(0)
	,mTransparentEnable(False)
{
	mGeometryUsage=DEVILX_NEW IGeometryUsageImp();
}

NSDevilX::NSRenderSystem::ISubEntityImp::~ISubEntityImp()
{
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

Void NSDevilX::NSRenderSystem::ISubEntityImp::setAmbientModel(IEnum::EMaterialAmbientModel model)
{
	if(model!=mAmbientModel)
	{
		notify(EMessage_BeginAmbientModelChange);
		mAmbientModel=model;
		notify(EMessage_EndAmbientModelChange);
	}
}

IEnum::EMaterialAmbientModel NSDevilX::NSRenderSystem::ISubEntityImp::getAmbientModel() const
{
	return mAmbientModel;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setDiffuseModel(IEnum::EMaterialDiffuseModel model)
{
	if(model!=mDiffuseModel)
	{
		notify(EMessage_BeginDiffuseModelChange);
		mDiffuseModel=model;
		notify(EMessage_EndDiffuseModelChange);
	}
}

IEnum::EMaterialDiffuseModel NSDevilX::NSRenderSystem::ISubEntityImp::getDiffuseModel() const
{
	return mDiffuseModel;
}

Void NSDevilX::NSRenderSystem::ISubEntityImp::setSpecularModel(IEnum::EMaterialSpecularModel model)
{
	if(model!=mSpecularModel)
	{
		notify(EMessage_BeginSpecularModelChange);
		mSpecularModel=model;
		notify(EMessage_EndSpecularModelChange);
	}
}

IEnum::EMaterialSpecularModel NSDevilX::NSRenderSystem::ISubEntityImp::getSpecularModel() const
{
	return mSpecularModel;
}

IColourUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getAlphaColourUnitState()
{
	if(!mAlphaColour)
	{
		notify(EMessage_BeginAlphaColourCreate);
		mAlphaColour=DEVILX_NEW IColourUnitStateImp(CColour::EType_Alpha);
		notify(EMessage_EndAlphaColourCreate);
	}
	return mAlphaColour;
}

IColourUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getEmissiveColourUnitState()
{
	if(!mEmissiveColour)
	{
		notify(EMessage_BeginEmissiveColourCreate);
		mEmissiveColour=DEVILX_NEW IColourUnitStateImp(CColour::EType_RGB);
		notify(EMessage_EndEmissiveColourCreate);
	}
	return mEmissiveColour;
}

IColourUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getDiffuseColourUnitState()
{
	if(!mDiffuseColour)
	{
		notify(EMessage_BeginDiffuseColourCreate);
		mDiffuseColour=DEVILX_NEW IColourUnitStateImp(CColour::EType_RGB);
		notify(EMessage_EndDiffuseColourCreate);
	}
	return mDiffuseColour;
}

IColourUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getSpecularColourUnitState()
{
	if(!mSpecularColour)
	{
		notify(EMessage_BeginSpecularColourCreate);
		mSpecularColour=DEVILX_NEW IColourUnitStateImp(CColour::EType_RGB);
		notify(EMessage_EndSpecularColourCreate);
	}
	return mSpecularColour;
}

ITextureUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getDiffuseTextureUnitState()
{
	if(!mDiffuseTexture)
	{
		notify(EMessage_BeginDiffuseTextureCreate);
		mDiffuseTexture=DEVILX_NEW ITextureUnitStateImp();
		notify(EMessage_EndDiffuseTextureCreate);
	}
	return mDiffuseTexture;
}

ITextureUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getSpecularTextureUnitState()
{
	if(!mSpecularTexture)
	{
		notify(EMessage_BeginSpecularTextureCreate);
		mSpecularTexture=DEVILX_NEW ITextureUnitStateImp();
		notify(EMessage_EndSpecularTextureCreate);
	}
	return mSpecularTexture;
}

ITextureUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getNormalTextureUnitState()
{
	if(!mNormalTexture)
	{
		notify(EMessage_BeginNormalTextureCreate);
		mNormalTexture=DEVILX_NEW ITextureUnitStateImp();
		notify(EMessage_EndNormalTextureCreate);
	}
	return mNormalTexture;
}

IFloatUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getMetallicUnitState()
{
	if(!mMetallicValue)
	{
		notify(EMessage_BeginMetallicValueCreate);
		mMetallicValue=DEVILX_NEW IFloatUnitStateImp();
		notify(EMessage_EndMetallicValueCreate);
	}
	return mMetallicValue;
}

IFloatUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getRoughnessUnitState()
{
	if(!mRoughnessValue)
	{
		notify(EMessage_BeginRoughnessValueCreate);
		mRoughnessValue=DEVILX_NEW IFloatUnitStateImp();
		notify(EMessage_EndRoughnessValueCreate);
	}
	return mRoughnessValue;
}

IFloatUnitState * NSDevilX::NSRenderSystem::ISubEntityImp::getSpecularPowerUnitState()
{
	if(!mSpecularPowerValue)
	{
		notify(EMessage_BeginSpecularPowerValueCreate);
		mSpecularPowerValue=DEVILX_NEW IFloatUnitStateImp(10.0f);
		notify(EMessage_EndSpecularPowerValueCreate);
	}
	return mSpecularPowerValue;
}
