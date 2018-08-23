#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBufferImp;
		class IBufferOperator_SkeletonAnimationImp
			:public IBufferOperator_SkeletonAnimation
			,public TBaseObject<IBufferOperator_SkeletonAnimationImp>
		{
		protected:
			IBufferImp*const mBuffer;
			const CMatrix4F * mTransforms;
			UInt32 mTransformCount;
			TVector(Byte) mDatas;
		public:
			IBufferOperator_SkeletonAnimationImp(IBufferImp * buffer);
			~IBufferOperator_SkeletonAnimationImp();

			// Í¨¹ý IBufferOperator_SkeletonAnimation ¼Ì³Ð
			virtual Void setTransforms(const CMatrix4F * transforms,UInt32 count) override;
			virtual const CMatrix4F * getTransforms() const override;
			virtual UInt32 getTransformsCount() const override;
			virtual Void updateData(UInt32 offsetTransform=0,UInt32 count=0) override;
		};
	}
}