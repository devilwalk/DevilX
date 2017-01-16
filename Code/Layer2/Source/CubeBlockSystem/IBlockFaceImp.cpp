#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockSystem;

NSDevilX::NSCubeBlockSystem::IBlockFaceImp::IBlockFaceImp()
	:mRenderMaterial(nullptr)
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
