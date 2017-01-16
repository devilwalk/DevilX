#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;

NSDevilX::NSPhysicalSystem::IMeshImp::IMeshImp(const String & name)
	:mName(name)
	,mGeometry(0)
{}

NSDevilX::NSPhysicalSystem::IMeshImp::~IMeshImp()
{
	if(!ISystemImp::getSingleton().isExit())
	{
		notify(EMessage_BeginDestruction);
		mSubMeshes.destroyAll();
		notify(EMessage_EndDestruction);
	}
}

const String & NSDevilX::NSPhysicalSystem::IMeshImp::getName() const
{
	return mName;
}

Void NSDevilX::NSPhysicalSystem::IMeshImp::setGeometry(IGeometry * geometry)
{
	if(geometry!=mGeometry)
	{
		notify(EMessage_BeginGeometryChange);
		mGeometry=static_cast<IGeometryImp*>(geometry);
		notify(EMessage_EndGeometryChange);
	}
}

IGeometry * NSDevilX::NSPhysicalSystem::IMeshImp::getGeometry() const
{
	return mGeometry;
}

ISubMesh * NSDevilX::NSPhysicalSystem::IMeshImp::createSubMesh(const String & name)
{
	notify(EMessage_BeginSubMeshCreate);
	assert(!mSubMeshes.has(name));
	ISubMeshImp * ret=DEVILX_NEW ISubMeshImp(name,this);
	mSubMeshes.add(name,ret);
	notify(EMessage_EndSubMeshCreate,ret);
	return ret;
}

Void NSDevilX::NSPhysicalSystem::IMeshImp::destroySubMesh(ISubMesh * subMesh)
{
	notify(EMessage_BeginSubMeshDestroy,static_cast<ISubMeshImp*>(subMesh));
	mSubMeshes.destroy(subMesh->getName());
	notify(EMessage_EndSubMeshDestroy,static_cast<ISubMeshImp*>(subMesh));
}

ISubMesh * NSDevilX::NSPhysicalSystem::IMeshImp::getSubMesh(const String & name) const
{
	return mSubMeshes.get(name);
}

UInt32 NSDevilX::NSPhysicalSystem::IMeshImp::getSubMeshCount() const
{
	return static_cast<UInt32>(mSubMeshes.size());
}

ISubMesh * NSDevilX::NSPhysicalSystem::IMeshImp::getSubMesh(UInt32 index) const
{
	return mSubMeshes.get(index);
}
