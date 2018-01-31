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
			CFloat2 mStaticUVOffset;
			CFloat2 mStaticUVScale;
		public:
			IBlockFaceImp();
			~IBlockFaceImp();

			// Inherited via IBlockFace
			virtual Void setRenderMaterial(IRenderMaterial * material) override;
			virtual IRenderMaterial * getRenderMaterial() const override;

			// Í¨¹ý IBlockFace ¼Ì³Ð
			virtual Void setUVStaticTransform(const CFloat2 & offset, const CFloat2 & scale) override;
			virtual const CFloat2 & getUVStaticOffset() const override;
			virtual const CFloat2 & getUVStaticScale() const override;
		};
	}
}