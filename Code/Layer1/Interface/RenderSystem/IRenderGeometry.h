#pragma once
#include "IRenderEnum.h"
#include "IRenderBufferUsage.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeoemtry;
		class IVertexBufferUsage
		{
		protected:
			virtual ~IVertexBufferUsage()
			{
			}
		public:
			virtual IBufferUsage * queryInterface_IBufferUsage()const=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setBuffer(IBuffer * buffer)=0;
			virtual IBuffer * getBuffer()const=0;
			virtual Void setFormat(UInt32 alignedByteOffset,IEnum::EVertexElementFormat format,const String & semanticName,UInt32 semanticIndex=0)=0;
		};
		class IIndexBufferUsage
		{
		protected:
			virtual ~IIndexBufferUsage()
			{
			}
		public:
			virtual IBufferUsage * queryInterface_IBufferUsage()const=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setBuffer(IBuffer * buffer)=0;
			virtual IBuffer * getBuffer()const=0;
			virtual Void setFormat(IEnum::EIndexFormat format)=0;
		};
		class IGeometry
		{
		protected:
			virtual ~IGeometry(){}
		public:
			virtual const String & getName()const=0;
			virtual IVertexBufferUsage * getVertexBufferUsage(UInt32 slot)=0;
			virtual IIndexBufferUsage * getIndexBufferUsage()=0;
			virtual Void setOperationType(IEnum::EOperationType type)=0;
			virtual IEnum::EOperationType getOperationType()const=0;
		};
	}
}