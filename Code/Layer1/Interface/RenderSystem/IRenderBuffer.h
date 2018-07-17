#pragma once
#include "IRenderBufferOperator_SkeletonAnimation.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBuffer
		{
		protected:
			virtual ~IBuffer(){}
		public:
			virtual IBufferOperator_SkeletonAnimation * queryInterface_IBufferOperator_SkeletonAnimation()=0;
			virtual const String & getName()const=0;
			virtual Void setSize(UInt32 sizeInBytes)=0;
			virtual UInt32 getSize()const=0;
			virtual Void setDatas(ConstVoidPtr datas)=0;
			virtual ConstVoidPtr getDatas()const=0;
			virtual Void updateData(UInt32 offsetInBytes=0,UInt32 sizeInBytes=0)=0;
		};
	}
}