#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBufferUsage
		{
		protected:
			virtual ~IBufferUsage(){}
		public:
			virtual Void setOffset(UInt32 offsetInBytes)=0;
			virtual UInt32 getOffset()const=0;
			virtual Void setSize(UInt32 sizeInBytes)=0;
			virtual UInt32 getSize()const=0;
		};
	}
}