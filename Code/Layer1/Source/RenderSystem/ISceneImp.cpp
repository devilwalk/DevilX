#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::ISceneImp::ISceneImp(const String & name,IEnum::ESceneManagerAlgorithm algorithm)
	:mName(name)
	,mManager(nullptr)
	,mAmbientColour(CFloatRGBA::sWhite)
{
	switch(algorithm)
	{
	case IEnum::ESceneManagerAlgorithm_Simple:
		mManager=DEVILX_NEW CSimpleSceneManager(this);
		break;
	}
}

NSDevilX::NSRenderSystem::ISceneImp::~ISceneImp()
{
	DEVILX_DELETE(mManager);
}

const String & NSDevilX::NSRenderSystem::ISceneImp::getName() const
{
	return mName;
}

IEnum::ESceneManagerAlgorithm NSDevilX::NSRenderSystem::ISceneImp::getAlgorithm() const
{
	return mManager->getAlgorithm();
}

ICamera * NSDevilX::NSRenderSystem::ISceneImp::createCamera(const String & name)
{
	if(mCameras.has(name))
		return nullptr;
	notify(EMessage_BeginCameraCreate);
	ICameraImp * ret=DEVILX_NEW ICameraImp(name,this);
	mCameras[name]=ret;
	notify(EMessage_EndCameraCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::ISceneImp::destroyCamera(ICamera * camera)
{
	if(!mCameras.has(camera->queryInterface_ISceneElement()->getName()))
		return;
	notify(EMessage_BeginCameraDestroy,static_cast<ICameraImp*>(camera));
	mCameras.destroy(camera->queryInterface_ISceneElement()->getName());
	notify(EMessage_EndCameraDestroy);
}

ICamera * NSDevilX::NSRenderSystem::ISceneImp::getCamera(const String & name) const
{
	return mCameras.get(name);
}

ILight * NSDevilX::NSRenderSystem::ISceneImp::createLight(const String & name,IEnum::ELightType type)
{
	if(mLights.has(name))
		return nullptr;
	notify(EMessage_BeginLightCreate);
	ILightImp * ret=DEVILX_NEW ILightImp(name,type,this);
	mLights[name]=ret;
	notify(EMessage_EndLightCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::ISceneImp::destroyLight(ILight * light)
{
	if(!mLights.has(light->queryInterface_ISceneElement()->getName()))
		return;
	notify(EMessage_BeginLightDestroy,static_cast<ILightImp*>(light));
	mLights.destroy(light->queryInterface_ISceneElement()->getName());
	notify(EMessage_EndLightDestroy);
}

ILight * NSDevilX::NSRenderSystem::ISceneImp::getLight(const String & name) const
{
	return mLights.get(name);
}

IEntity * NSDevilX::NSRenderSystem::ISceneImp::createEntity(const String & name)
{
	if(mEntities.has(name))
		return nullptr;
	notify(EMessage_BeginEntityCreate);
	IEntityImp * ret=DEVILX_NEW IEntityImp(name,this);
	mEntities[name]=ret;
	notify(EMessage_EndEntityCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::ISceneImp::destroyEntity(IEntity * obj)
{
	if(!mEntities.has(obj->queryInterface_ISceneElement()->getName()))
		return;
	notify(EMessage_BeginEntityDestroy,static_cast<IEntityImp*>(obj));
	mEntities.destroy(obj->queryInterface_ISceneElement()->getName());
	notify(EMessage_EndEntityDestroy);
}

IEntity * NSDevilX::NSRenderSystem::ISceneImp::getEntity(const String & name) const
{
	return mEntities.get(name);
}

IVisibleArea * NSDevilX::NSRenderSystem::ISceneImp::createVisibleArea(const String & name)
{
	if(mVisibleAreas.has(name))
		return nullptr;
	notify(EMessage_BeginVisibleAreaCreate);
	auto * ret=DEVILX_NEW IVisibleAreaImp(name,this);
	mVisibleAreas[name]=ret;
	notify(EMessage_EndVisibleAreaCreate,ret);
	return ret;
}

IVisibleArea * NSDevilX::NSRenderSystem::ISceneImp::getVisibleArea(const String & name) const
{
	return mVisibleAreas.get(name);
}

Void NSDevilX::NSRenderSystem::ISceneImp::destroyVisibleArea(IVisibleArea * area)
{
	if(!mVisibleAreas.has(area->getName()))
		return;
	notify(EMessage_BeginVisibleAreaDestroy,static_cast<IVisibleAreaImp*>(area));
	mVisibleAreas.destroy(area->getName());
	notify(EMessage_EndVisibleAreaDestroy);
}

ISky * NSDevilX::NSRenderSystem::ISceneImp::createSky(const String & name)
{
	if(mSkys.has(name))
		return nullptr;
	notify(EMessage_BeginSkyCreate);
	auto * ret=DEVILX_NEW ISkyImp(name,this);
	mSkys[name]=ret;
	notify(EMessage_EndSkyCreate,ret);
	return ret;
}

ISky * NSDevilX::NSRenderSystem::ISceneImp::getSky(const String & name) const
{
	return mSkys.get(name);
}

Void NSDevilX::NSRenderSystem::ISceneImp::destroySky(ISky * sky)
{
	if(!mSkys.has(sky->queryInterface_ISceneElement()->getName()))
		return;
	notify(EMessage_BeginSkyDestroy,static_cast<ISkyImp*>(sky));
	mSkys.destroy(sky->queryInterface_ISceneElement()->getName());
	notify(EMessage_EndSkyDestroy);
}

IQueryObject * NSDevilX::NSRenderSystem::ISceneImp::createQueryObject(const String & name)
{
	if(mQueryObjects.has(name))
		return nullptr;
	notify(EMessage_BeginQueryObjectCreate);
	auto * ret=DEVILX_NEW IQueryObjectImp(name,this);
	mQueryObjects[name]=ret;
	notify(EMessage_EndQueryObjectCreate,ret);
	return ret;
}

IQueryObject * NSDevilX::NSRenderSystem::ISceneImp::getQueryObject(const String & name) const
{
	return mQueryObjects.get(name);
}

Void NSDevilX::NSRenderSystem::ISceneImp::destroyQueryObject(IQueryObject * obj)
{
	if(!mQueryObjects.has(obj->queryInterface_ISceneElement()->getName()))
		return;
	notify(EMessage_BeginQueryObjectDestroy,static_cast<IQueryObjectImp*>(obj));
	mQueryObjects.destroy(obj->queryInterface_ISceneElement()->getName());
	notify(EMessage_EndQueryObjectDestroy);
}

Void NSDevilX::NSRenderSystem::ISceneImp::setAmbientColour(const CColour & colour)
{
	if(colour!=getAmbientColour())
	{
		notify(EMessage_BeginAmbientColourChange);
		mAmbientColour=colour;
		notify(EMessage_EndAmbientColourChange);
	}
}

const CColour & NSDevilX::NSRenderSystem::ISceneImp::getAmbientColour() const
{
	// TODO: insert return statement here
	return mAmbientColour;
}
