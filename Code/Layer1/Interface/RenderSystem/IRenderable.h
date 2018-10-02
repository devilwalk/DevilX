#pragma once
#include "IRenderGeometry.h"
#include "IRenderMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryUsage
		{
		protected:
			virtual ~IGeometryUsage(){ }
		public:
			//The location of the first index read by the GPU from the index buffer.
			virtual Void setStartIndexLocation(UInt32 location)=0;
			virtual UInt32 getStartIndexLocation()const=0;
			virtual Void setIndexCount(UInt32 count)=0;
			virtual UInt32 getIndexCount()const=0;
			//A value added to each index before reading a vertex from the vertex buffer.
			virtual Void setBaseVertexLocation(UInt32 location)=0;
			virtual UInt32 getBaseVertexLocation()const=0;
			virtual Void setVertexCount(UInt32 count)=0;
			virtual UInt32 getVertexCount()const=0;
			//Index of the first vertex, which is usually an offset in a vertex buffer.
			virtual Void setStartVertexLocation(UInt32 location)=0;
			virtual UInt32 getStartVertexLocation()const=0;
		};
		class IRenderable
		{
		protected:
			virtual ~IRenderable(){ }
		public:
			virtual IGeometryUsage * queryInterface_IGeometryUsage()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
			virtual Void setMaterial(IMaterial * material)=0;
			virtual IMaterial * getMaterial()const=0;
		};
	}
}