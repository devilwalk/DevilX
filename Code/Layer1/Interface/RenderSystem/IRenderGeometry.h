#pragma once
#include "IRenderEnum.h"
#include "IRenderVertexBuffer.h"
#include "IRenderIndexBuffer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometry
		{
		protected:
			virtual ~IGeometry(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setVertexBuffer(IVertexBuffer * buffer)=0;
			virtual IVertexBuffer * getVertexBuffer()const=0;
			virtual Void setIndexBuffer(IIndexBuffer * buffer)=0;
			virtual IIndexBuffer * getIndexBuffer()const=0;
		};
	}
}