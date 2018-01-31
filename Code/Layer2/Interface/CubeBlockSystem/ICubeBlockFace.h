#pragma once
#include "ICubeBlockRenderMaterial.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IBlockFace
		{
		protected:
			virtual ~IBlockFace(){}
		public:
			virtual Void setRenderMaterial(IRenderMaterial * material)=0;
			virtual IRenderMaterial * getRenderMaterial()const=0;
			virtual Void setUVStaticTransform(const CFloat2 & offset,const CFloat2 & scale)=0;
			virtual const CFloat2 & getUVStaticOffset()const=0;
			virtual const CFloat2 & getUVStaticScale()const=0;
		};
	}
}