#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IIndexBuffer
		{
		protected:
		public:
			virtual Void setCount(UInt32 count)=0;
			virtual UInt32 getCount()const=0;
			virtual Void setIndices(const UInt32 * indices)=0;
			virtual Void updateIndices()=0;
			virtual const UInt32 * getIndices()const=0;
		};
	}
}