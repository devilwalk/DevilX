#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
NSDevilX::NSPhysicalSystem::IGeometryImp::IGeometryImp(const String & name)
	:mName(name)
	,mVertexCount(0)
	,mIndexCount(0)
	,mPositions(0)
	,mIndices(0)
{}

NSDevilX::NSPhysicalSystem::IGeometryImp::~IGeometryImp()
{}

const String & NSDevilX::NSPhysicalSystem::IGeometryImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSPhysicalSystem::IGeometryImp::setVertexCount(UInt32 vertexCount)
{
	if(vertexCount!=mVertexCount)
	{
		notify(EMessage_BeginVertexCountChange);
		mVertexCount=vertexCount;
		notify(EMessage_EndVertexCountChange);
	}
}

UInt32 NSDevilX::NSPhysicalSystem::IGeometryImp::getVertexCount()const
{
	return mVertexCount;
}

Void NSDevilX::NSPhysicalSystem::IGeometryImp::setIndexCount(UInt32 indexCount)
{
	if(indexCount!=mIndexCount)
	{
		notify(EMessage_BeginIndexCountChange);
		mIndexCount=indexCount;
		notify(EMessage_EndIndexCountChange);
	}
}

UInt32 NSDevilX::NSPhysicalSystem::IGeometryImp::getIndexCount()const
{
	return mIndexCount;
}

Void NSDevilX::NSPhysicalSystem::IGeometryImp::setPositions(const CFloat3 * positions)
{
	if(positions!=mPositions)
	{
		notify(EMessage_BeginPositionsChange);
		mPositions=positions;
		notify(EMessage_EndPositionsChange);
	}
}

const CFloat3 * NSDevilX::NSPhysicalSystem::IGeometryImp::getPositions()const
{
	return mPositions;
}

Void NSDevilX::NSPhysicalSystem::IGeometryImp::setIndices(const UInt32 * indices)
{
	if(indices!=mIndices)
	{
		notify(EMessage_BeginIndicesChange);
		mIndices=indices;
		notify(EMessage_EndIndicesChange);
	}
}

const UInt32 * NSDevilX::NSPhysicalSystem::IGeometryImp::getIndices()const
{
	return mIndices;
}