#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
NSDevilX::NSPhysicalSystem::IResourceManagerImp::IResourceManagerImp()
{}

NSDevilX::NSPhysicalSystem::IResourceManagerImp::~IResourceManagerImp()
{
}

IMesh * NSDevilX::NSPhysicalSystem::IResourceManagerImp::createMesh(const String & name)
{
	notify(EMessage_BeginMeshCreate);
	assert(!mMeshes.has(name));
	IMeshImp * ret=DEVILX_NEW IMeshImp(name);
	mMeshes[name]=ret;
	notify(EMessage_EndMeshCreate,ret);
	return ret;
}

Void NSDevilX::NSPhysicalSystem::IResourceManagerImp::destroyMesh(IMesh * mesh)
{
	notify(EMessage_BeginMeshDestroy,static_cast<IMeshImp*>(mesh));
	assert(mMeshes.has(mesh->getName()));
	mMeshes.destroy(mesh->getName());
	notify(EMessage_EndMeshDestroy);
}

IMesh * NSDevilX::NSPhysicalSystem::IResourceManagerImp::getMesh(const String & name) const
{
	return mMeshes.get(name);
}

IGeometry * NSDevilX::NSPhysicalSystem::IResourceManagerImp::createGeometry(const String & name)
{
	notify(EMessage_BeginGeometryCreate);
	assert(!mGeometrys.has(name));
	IGeometryImp * ret=DEVILX_NEW IGeometryImp(name);
	mGeometrys[name]=ret;
	notify(EMessage_EndGeometryCreate,ret);
	return ret;
}

Void NSDevilX::NSPhysicalSystem::IResourceManagerImp::destroyGeometry(IGeometry * geometry)
{
	notify(EMessage_BeginGeometryDestroy,static_cast<IGeometryImp*>(geometry));
	assert(mGeometrys.has(geometry->getName()));
	mGeometrys.destroy(geometry->getName());
	notify(EMessage_EndGeometryDestroy);
}

IGeometry * NSDevilX::NSPhysicalSystem::IResourceManagerImp::getGeometry(const String & name) const
{
	return mGeometrys.get(name);
}
