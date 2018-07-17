#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBufferOperator_SkeletonAnimation
		{
		protected:
			virtual ~IBufferOperator_SkeletonAnimation(){}
		public:
			virtual Void setTransforms(const CMatrix4F * transforms,UInt32 count)=0;
			virtual const CMatrix4F * getTransforms()const=0;
			virtual UInt32 getTransformsCount()const=0;
			virtual Void updateData(UInt32 offsetTransform=0,UInt32 count=0)=0;
		};
	}
}