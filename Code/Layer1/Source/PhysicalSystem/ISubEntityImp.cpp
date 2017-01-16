#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;

NSDevilX::NSPhysicalSystem::ISubEntityImp::ISubEntityImp(ISubMeshImp * subMesh,IEntityImp * entity)
	:mSubMesh(subMesh)
	,mEntity(entity)
{}

NSDevilX::NSPhysicalSystem::ISubEntityImp::~ISubEntityImp()
{}

IEntity * NSDevilX::NSPhysicalSystem::ISubEntityImp::getEntity() const
{
	return mEntity;
}

ISubMesh * NSDevilX::NSPhysicalSystem::ISubEntityImp::getSubMesh() const
{
	return mSubMesh;
}

Void NSDevilX::NSPhysicalSystem::ISubEntityImp::setQueryMask(UInt32 mask)
{
	mQueryMask=mask;
}

UInt32 NSDevilX::NSPhysicalSystem::ISubEntityImp::getQueryMask() const
{
	return mQueryMask;
}