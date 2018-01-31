#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockSystem;

NSDevilX::NSCubeBlockSystem::IBlockFaceImp::IBlockFaceImp()
	:mRenderMaterial(nullptr)
	,mStaticUVOffset(CFloat2::sZero)
	,mStaticUVScale(CFloat2::sOne)
{}

NSDevilX::NSCubeBlockSystem::IBlockFaceImp::~IBlockFaceImp()
{}

Void NSDevilX::NSCubeBlockSystem::IBlockFaceImp::setRenderMaterial(IRenderMaterial * material)
{
	mRenderMaterial=static_cast<IRenderMaterialImp*>(material);
}

IRenderMaterial * NSDevilX::NSCubeBlockSystem::IBlockFaceImp::getRenderMaterial() const
{
	return mRenderMaterial;
}

Void NSDevilX::NSCubeBlockSystem::IBlockFaceImp::setUVStaticTransform(const CFloat2 & offset, const CFloat2 & scale)
{
	if((offset!=mStaticUVOffset)
		||(scale!=mStaticUVScale)
		)
	{
		mStaticUVOffset=offset;
		mStaticUVScale=scale;
	}
}

const CFloat2 & NSDevilX::NSCubeBlockSystem::IBlockFaceImp::getUVStaticOffset() const
{
	// TODO: 在此处插入 return 语句
	return mStaticUVOffset;
}

const CFloat2 & NSDevilX::NSCubeBlockSystem::IBlockFaceImp::getUVStaticScale() const
{
	// TODO: 在此处插入 return 语句
	return mStaticUVScale;
}
