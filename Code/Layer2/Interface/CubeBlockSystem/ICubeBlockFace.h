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
		};
	}
}