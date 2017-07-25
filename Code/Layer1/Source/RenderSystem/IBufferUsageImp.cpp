#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IBufferUsageImp::IBufferUsageImp()
	:mOffsetInBytes(0)
	,mSizeInBytes(0)
{}

NSDevilX::NSRenderSystem::IBufferUsageImp::~IBufferUsageImp()
{}

Void NSDevilX::NSRenderSystem::IBufferUsageImp::setOffset(UInt32 offsetInBytes)
{
	if(getOffset()!=offsetInBytes)
	{
		notify(EMessage_BeginOffsetChange);
		mOffsetInBytes=offsetInBytes;
		notify(EMessage_EndOffsetChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IBufferUsageImp::getOffset() const
{
	return mOffsetInBytes;
}

Void NSDevilX::NSRenderSystem::IBufferUsageImp::setSize(UInt32 sizeInBytes)
{
	if(getSize()!=sizeInBytes)
	{
		notify(EMessage_BeginSizeChange);
		mSizeInBytes=sizeInBytes;
		notify(EMessage_EndSizeChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IBufferUsageImp::getSize() const
{
	return mSizeInBytes;
}
