#pragma once
#include "IRenderEnum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IVertexBuffer
		{
		protected:
			virtual ~IVertexBuffer(){}
		public:
			virtual Void setCount(UInt32 count)=0;
			virtual UInt32 getCount()const=0;
			virtual Void setPositions(const CFloat3 * positions)=0;
			virtual Void updatePositions(UInt32 offset=0,UInt32 count=0)=0;
			virtual const CFloat3 * getPositions()const=0;
			virtual Void setNormals(const CFloat3 * normals)=0;
			virtual Void updateNormals(UInt32 offset=0,UInt32 count=0)=0;
			virtual const CFloat3 * getNormals()const=0;
			virtual Void setTangents(const CFloat3 * tangents)=0;
			virtual Void updateTangents(UInt32 offset=0,UInt32 count=0)=0;
			virtual const CFloat3 * getTangents()const=0;
			virtual Void setTextureCoords(const CFloat2 * uvs,IEnum::ETextureCoord index=IEnum::ETextureCoord_0)=0;
			virtual Void updateTextureCoords(UInt32 offset=0,UInt32 count=0,IEnum::ETextureCoord index=IEnum::ETextureCoord_0)=0;
			virtual const CFloat2 * getTextureCoords(IEnum::ETextureCoord index=IEnum::ETextureCoord_0)const=0;
			virtual Void setBlendWeights(const CFloat4 * blendWeights)=0;
			virtual Void updateBlendWeights(UInt32 offset=0,UInt32 count=0)=0;
			virtual const CFloat4 * getBlendWeights()const=0;
			virtual Void setBlendIndices(const UInt8 * blendIndices)=0;
			virtual Void updateBlendIndices(UInt32 offset=0,UInt32 count=0)=0;
			virtual const UInt8 * getBlendIndices()const=0;
			virtual Void setDiffuses(const RGBA * colours)=0;
			virtual Void updateDiffuses(UInt32 offset=0,UInt32 count=0)=0;
			virtual const RGBA * getDiffuses()const=0;
		};
	}
}