#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IBufferOperator_SkeletonAnimationImp::IBufferOperator_SkeletonAnimationImp(IBufferImp * buffer)
	:mBuffer(buffer)
	,mTransforms(nullptr)
	,mTransformCount(0)
{
}

NSDevilX::NSRenderSystem::IBufferOperator_SkeletonAnimationImp::~IBufferOperator_SkeletonAnimationImp()
{
}

Void NSDevilX::NSRenderSystem::IBufferOperator_SkeletonAnimationImp::setTransforms(const CMatrix4F * transforms,UInt32 count)
{
	if((mTransforms!=transforms)
		||(mTransformCount!=count))
	{
		mTransforms=transforms;
		mTransformCount=count;
		mDatas.resize(mTransformCount*3*sizeof(CFloat4));
		for(UInt32 i=0;i<mTransformCount;++i)
		{
			reinterpret_cast<CFloat4*>(&mDatas[0])[i*3]=mTransforms[i].colume(0);
			reinterpret_cast<CFloat4*>(&mDatas[0])[i*3+1]=mTransforms[i].colume(1);
			reinterpret_cast<CFloat4*>(&mDatas[0])[i*3+2]=mTransforms[i].colume(2);
		}
		mBuffer->setDatas(&mDatas[0]);
		mBuffer->setSize(static_cast<UInt32>(mDatas.size()));
		mBuffer->updateData();
	}
}

const CMatrix4F * NSDevilX::NSRenderSystem::IBufferOperator_SkeletonAnimationImp::getTransforms() const
{
	return mTransforms;
}

UInt32 NSDevilX::NSRenderSystem::IBufferOperator_SkeletonAnimationImp::getTransformsCount() const
{
	return mTransformCount;
}

Void NSDevilX::NSRenderSystem::IBufferOperator_SkeletonAnimationImp::updateData(UInt32 offsetTransform=0,UInt32 count=0)
{
	mBuffer->updateData(offsetTransform*3*sizeof(CFloat4),count*3*sizeof(CFloat4));
}
