#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;

NSDevilX::NSPhysicalSystem::ISubMeshImp::ISubMeshImp(const String & name,IMeshImp * mesh)
	:mName(name)
	,mMesh(mesh)
	,mVertexStart(0)
	,mIndexStart(0)
	,mIndexCount(0)
{
}

NSDevilX::NSPhysicalSystem::ISubMeshImp::~ISubMeshImp()
{
	if(!ISystemImp::getSingleton().isExit())
	{
		notify(EMessage_BeginDestruction);
		notify(EMessage_EndDestruction);
	}
}

IMesh * NSDevilX::NSPhysicalSystem::ISubMeshImp::getMesh() const
{
	return mMesh;
}

const String & NSDevilX::NSPhysicalSystem::ISubMeshImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSPhysicalSystem::ISubMeshImp::setVertexStart(UInt32 vertexStart)
{
	if(vertexStart!=mVertexStart)
	{
		notify(EMessage_BeginVertexStartChange);
		mVertexStart=vertexStart;
		notify(EMessage_EndVertexStartChange);
	}
}

UInt32 NSDevilX::NSPhysicalSystem::ISubMeshImp::getVertexStart() const
{
	return mVertexStart;
}

Void NSDevilX::NSPhysicalSystem::ISubMeshImp::setIndexStart(UInt32 indexStart)
{
	if(indexStart!=mIndexStart)
	{
		notify(EMessage_BeginIndexStartChange);
		mIndexStart=indexStart;
		notify(EMessage_EndIndexStartChange);
	}
}

UInt32 NSDevilX::NSPhysicalSystem::ISubMeshImp::getIndexStart() const
{
	return mIndexStart;
}

Void NSDevilX::NSPhysicalSystem::ISubMeshImp::setIndexCount(UInt32 indexCount)
{
	if(indexCount!=mIndexCount)
	{
		notify(EMessage_BeginIndexCountChange);
		mIndexCount=indexCount;
		notify(EMessage_EndIndexCountChange);
	}
}

UInt32 NSDevilX::NSPhysicalSystem::ISubMeshImp::getIndexCount() const
{
	return mIndexCount;
}
