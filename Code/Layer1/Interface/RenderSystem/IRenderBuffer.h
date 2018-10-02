#pragma once
#include "IRenderEnum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBuffer
		{
		protected:
			virtual ~IBuffer(){}
		public:
			virtual const String & getName()const=0;
			virtual Void initialize(IEnum::EBufferType type,UInt32 sizeInBytes,UInt32 flag=IEnum::EBufferFlag_GPURead)=0;
			virtual IEnum::EBufferType getType()const=0;
			virtual UInt32 getSize()const=0;
			virtual Void updateData(ConstVoidPtr data,UInt32 offsetInBytes=0,UInt32 sizeInBytes=0)=0;
			virtual Void bind(UInt32 offsetInBytes,IEnum::EAutoPropgramParameterDataSource source)=0;
			virtual Void unbind(UInt32 offsetInBytes)=0;
		};
	}
}