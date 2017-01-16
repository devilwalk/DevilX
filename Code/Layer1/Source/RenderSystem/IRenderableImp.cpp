#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IRenderableImp::IRenderableImp(const String & name,IRenderableObjectImp * object)
	:mName(name)
	,mObject(object)
	,mGeometry(nullptr)
	,mGeometryUsage(nullptr)
	,mMaterial(nullptr)
	,mSky(nullptr)
{
	mGeometryUsage=DEVILX_NEW IGeometryUsageImp(this);
	mMaterial=DEVILX_NEW IMaterialImp(this);
}

NSDevilX::NSRenderSystem::IRenderableImp::~IRenderableImp()
{
	DEVILX_DELETE(mGeometryUsage);
	DEVILX_DELETE(mMaterial);
	DEVILX_DELETE(mSky);
}

ISky * NSDevilX::NSRenderSystem::IRenderableImp::queryInterface_ISky() const
{
	if(!mSky)
	{
		mSky=DEVILX_NEW ISkyImp(const_cast<IRenderableImp*>(this));
	}
	return mSky;
}

const String & NSDevilX::NSRenderSystem::IRenderableImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IRenderableObject * NSDevilX::NSRenderSystem::IRenderableImp::getObject() const
{
	return mObject;
}

IGeometryUsage * NSDevilX::NSRenderSystem::IRenderableImp::queryInterface_IGeometryUsage() const
{
	return mGeometryUsage;
}

IMaterial * NSDevilX::NSRenderSystem::IRenderableImp::queryInterface_IMaterial() const
{
	return mMaterial;
}

Void NSDevilX::NSRenderSystem::IRenderableImp::setVisible(Bool visible)
{
	if(visible!=mVisible)
	{
		CMessageNotifier::notify(EMessage_BeginVisibleChange);
		mVisible=visible;
		CMessageNotifier::notify(EMessage_EndVisibleChange);
	}
}

Bool NSDevilX::NSRenderSystem::IRenderableImp::getVisible() const
{
	return mVisible;
}

Void NSDevilX::NSRenderSystem::IRenderableImp::setGeometry(IGeometry * geometry)
{
	if(geometry!=getGeometry())
	{
		notify(EMessage_BeginGeometryChange,static_cast<IGeometryImp*>(geometry));
		mGeometry=static_cast<IGeometryImp*>(geometry);
		notify(EMessage_EndGeometryChange);
	}
}

IGeometry * NSDevilX::NSRenderSystem::IRenderableImp::getGeometry() const
{
	return mGeometry;
}
