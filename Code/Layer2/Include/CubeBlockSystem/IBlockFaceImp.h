#pragma once
#include "IRenderMaterialImp.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IBlockFaceImp
			:public IBlockFace
			,public TBaseObject<IBlockFaceImp>
		{
		protected:
			IRenderMaterialImp * mRenderMaterial;
		public:
			IBlockFaceImp();
			~IBlockFaceImp();

			// Inherited via IBlockFace
			virtual Void setRenderMaterial(IRenderMaterial * material) override;
			virtual IRenderMaterial * getRenderMaterial() const override;
		};
	}
}