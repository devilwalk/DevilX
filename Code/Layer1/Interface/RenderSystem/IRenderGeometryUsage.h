#pragma once
#include "IRenderEnum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryUsage
		{
		protected:
			virtual ~IGeometryUsage(){}
		public:
			virtual Void setVertexBufferOffset(UInt32 offset)=0;
			virtual UInt32 getVertexBufferOffset()const=0;
			virtual Void setIndexBufferOffset(UInt32 offset)=0;
			virtual UInt32 getIndexBufferOffset()const=0;
			virtual Void setVertexCount(UInt32 count)=0;
			virtual UInt32 getVertexCount()const=0;
			virtual Void setIndexCount(UInt32 count)=0;
			virtual UInt32 getIndexCount()const=0;
			virtual Void setOperationType(IEnum::EOperationType type)=0;
			virtual IEnum::EOperationType getOperationType()const=0;
		};
	}
}