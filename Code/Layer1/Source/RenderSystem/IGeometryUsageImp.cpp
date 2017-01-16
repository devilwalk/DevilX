#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::IGeometryUsageImp::IGeometryUsageImp(IRenderableImp * renderable)
	:mRenderable(renderable)
	,mVertexBufferOffset(0)
	,mIndexBufferOffset(0)
	,mVertexCount(0)
	,mIndexCount(0)
	,mOperationType(IEnum::EOperationType_TriangleList)
{
}

NSDevilX::NSRenderSystem::IGeometryUsageImp::~IGeometryUsageImp()
{}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setVertexBufferOffset(UInt32 offset)
{
	if(offset!=getVertexBufferOffset())
	{
		notify(EMessage_BeginVertexBufferOffsetChange);
		mVertexBufferOffset=offset;
		notify(EMessage_EndVertexBufferOffsetChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getVertexBufferOffset() const
{
	return mVertexBufferOffset;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setIndexBufferOffset(UInt32 offset)
{
	if(offset!=getIndexBufferOffset())
	{
		notify(EMessage_BeginIndexBufferOffsetChange);
		mIndexBufferOffset=offset;
		notify(EMessage_EndIndexBufferOffsetChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getIndexBufferOffset() const
{
	return mIndexBufferOffset;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setVertexCount(UInt32 count)
{
	if(count!=getVertexCount())
	{
		notify(EMessage_BeginVertexCountChange);
		mVertexCount=count;
		notify(EMessage_EndVertexCountChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getVertexCount() const
{
	return mVertexCount;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setIndexCount(UInt32 count)
{
	if(count!=getIndexCount())
	{
		notify(EMessage_BeginIndexCountChange);
		mIndexCount=count;
		notify(EMessage_EndIndexCountChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getIndexCount() const
{
	return mIndexCount;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setOperationType(IEnum::EOperationType type)
{
	if(type!=getOperationType())
	{
		notify(EMessage_BeginOperationTypeChange);
		mOperationType=type;
		notify(EMessage_EndOperationTypeChange);
	}
}

IEnum::EOperationType NSDevilX::NSRenderSystem::IGeometryUsageImp::getOperationType() const
{
	return mOperationType;
}
