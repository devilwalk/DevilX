#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IIndexBufferImp::IIndexBufferImp()
	:mCount(0)
{
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_IndexBufferCreate,this);
}

NSDevilX::NSRenderSystem::IIndexBufferImp::~IIndexBufferImp()
{
	if(!ISystemImp::getSingleton().isExit())
		static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_IndexBufferDestroy,this);
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::setCount(UInt32 count)
{
	if(count!=getCount())
	{
		mCount=count;
		addDirtyFlag(EDirtyFlag_Count);
	}
}

UInt32 NSDevilX::NSRenderSystem::IIndexBufferImp::getCount() const
{
	return mCount;
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::setIndices(const UInt32 * indices,UInt32 count)
{
	if(indices!=mIndices)
	{
		mIndices=indices;
		updateIndices(0,count);
	}
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::updateIndices(UInt32 offset,UInt32 count)
{
	mIndicesDirties.addDirty(offset,count);
	addDirtyFlag(EDirtyFlag_Index);
}

const UInt32 * NSDevilX::NSRenderSystem::IIndexBufferImp::getIndices() const
{
	return mIndices;
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::_preProcessDirtyFlagAdd(UInt32 flagIndex)
{
	notify(EMessage_BeginDirtyFlagAdd,&flagIndex);
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::_postProcessDirtyFlagAdd(UInt32 flagIndex)
{
	notify(EMessage_EndDirtyFlagAdd,&flagIndex);
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::_postProcessDirtyFlagRemove(UInt32 flagIndex)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Index:
		mIndicesDirties.clear();
		break;
	}
}
