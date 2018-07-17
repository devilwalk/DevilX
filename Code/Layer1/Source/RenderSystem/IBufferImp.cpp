#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IBufferImp::IBufferImp(const String & name,EType type)
	:mName(name)
	,mType(type)
	,mDatas(nullptr)
	,mSizeInBytes(0)
	,mSkeletonAnimationOperator(nullptr)
{}

NSDevilX::NSRenderSystem::IBufferImp::~IBufferImp()
{
	DEVILX_DELETE(mSkeletonAnimationOperator);
}

IBufferOperator_SkeletonAnimation * NSDevilX::NSRenderSystem::IBufferImp::queryInterface_IBufferOperator_SkeletonAnimation()
{
	if(!mSkeletonAnimationOperator)
		mSkeletonAnimationOperator=DEVILX_NEW IBufferOperator_SkeletonAnimationImp(this);
	return mSkeletonAnimationOperator;
}

const String & NSDevilX::NSRenderSystem::IBufferImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSRenderSystem::IBufferImp::setSize(UInt32 sizeInBytes)
{
	if(getSize()!=sizeInBytes)
	{
		mSizeInBytes=sizeInBytes;
		updateData();
		addDirtyFlag(EDirtyFlag_Size);
	}
}

UInt32 NSDevilX::NSRenderSystem::IBufferImp::getSize() const
{
	return mSizeInBytes;
}

Void NSDevilX::NSRenderSystem::IBufferImp::setDatas(ConstVoidPtr datas)
{
	if(getDatas()!=datas)
	{
		mDatas=datas;
		updateData();
	}
}

ConstVoidPtr NSDevilX::NSRenderSystem::IBufferImp::getDatas() const
{
	return mDatas;
}

Void NSDevilX::NSRenderSystem::IBufferImp::updateData(UInt32 offsetInBytes,UInt32 sizeInBytes)
{
	mDirties.addDirty(offsetInBytes,sizeInBytes?sizeInBytes:getSize());
	addDirtyFlag(EDirtyFlag_Datas);
}

Void NSDevilX::NSRenderSystem::IBufferImp::_preProcessDirtyFlagAdd(UInt32 flagIndex)
{
	notify(EMessage_BeginDirtyFlagAdd);
}

Void NSDevilX::NSRenderSystem::IBufferImp::_postProcessDirtyFlagAdd(UInt32 flagIndex)
{
	notify(EMessage_EndDirtyFlagAdd);
}

Void NSDevilX::NSRenderSystem::IBufferImp::_postProcessDirtyFlagRemove(UInt32 flagIndex)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Datas:
		mDirties.clear();
		break;
	}
}
