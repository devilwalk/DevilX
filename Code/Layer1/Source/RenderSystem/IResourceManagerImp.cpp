#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::IResourceManagerImp::IResourceManagerImp()
{}

NSDevilX::NSRenderSystem::IResourceManagerImp::~IResourceManagerImp()
{
}

IGeometry * NSDevilX::NSRenderSystem::IResourceManagerImp::createGeometry(const String & name)
{
	if(mGeometrys.has(name))
		return nullptr;
	notify(EMessage_BeginGeometryCreate);
	IGeometryImp * ret=DEVILX_NEW IGeometryImp(name);
	mGeometrys[name]=ret;
	notify(EMessage_EndGeometryCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyGeometry(IGeometry * geo)
{
	if(!mGeometrys.has(geo->getName()))
		return;
	notify(EMessage_BeginGeometryDestroy,static_cast<IGeometryImp*>(geo));
	mGeometrys.destroy(geo->getName());
	notify(EMessage_EndGeometryDestroy);
}

IGeometry * NSDevilX::NSRenderSystem::IResourceManagerImp::getGeometry(const String & name) const
{
	return mGeometrys.get(name);
}

ITexture * NSDevilX::NSRenderSystem::IResourceManagerImp::createTexture(const String & name,IEnum::ETextureType type)
{
	if(mTextures.has(name))
		return nullptr;
	notify(EMessage_BeginTextureCreate);
	ITextureImp * ret=nullptr;
	switch(type)
	{
	case IEnum::ETextureType_2D:
		ret=DEVILX_NEW ITexture2DImp(name);
		break;
	case IEnum::ETextureType_Cube:
		break;
	}
	mTextures[name]=ret;
	notify(EMessage_EndTextureCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyTexture(ITexture * texture)
{
	return Void();
}

ITexture * NSDevilX::NSRenderSystem::IResourceManagerImp::getTexture(const String & name) const
{
	return nullptr;
}
