#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IIndexBufferImp::IIndexBufferImp()
	:mBuffer(nullptr)
{
	mBuffer=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createIndexBuffer();
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_IndexBufferCreate,this);
}

NSDevilX::NSRenderSystem::IIndexBufferImp::~IIndexBufferImp()
{
	if(!ISystemImp::getSingleton().isExit())
	{
		static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(mBuffer);
		static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_IndexBufferDestroy,this);
	}
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::setCount(UInt32 count)
{
	mBuffer->setSize(count*sizeof(UInt32));
}

UInt32 NSDevilX::NSRenderSystem::IIndexBufferImp::getCount() const
{
	return mBuffer->getSize()/sizeof(UInt32);
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::setIndices(const UInt32 * indices)
{
	mBuffer->setDatas(indices);
}

Void NSDevilX::NSRenderSystem::IIndexBufferImp::updateIndices(UInt32 offset,UInt32 count)
{
	mBuffer->updateData(offset*sizeof(UInt32),count*sizeof(UInt32));
}

const UInt32 * NSDevilX::NSRenderSystem::IIndexBufferImp::getIndices() const
{
	return static_cast<const UInt32*>(mBuffer->getDatas());
}