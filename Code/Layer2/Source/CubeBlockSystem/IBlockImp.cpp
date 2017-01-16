#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockSystem;

NSDevilX::NSCubeBlockSystem::IBlockImp::IBlockImp(const String & name)
	:mName(name)
{
	for(auto & face_ref:mFaces)
	{
		face_ref=DEVILX_NEW IBlockFaceImp();
	}
}

NSDevilX::NSCubeBlockSystem::IBlockImp::~IBlockImp()
{
	for(auto face:mFaces)
		DEVILX_DELETE(face);
}

const String & NSDevilX::NSCubeBlockSystem::IBlockImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IBlockFace * NSDevilX::NSCubeBlockSystem::IBlockImp::getFace(IEnum::EBlockFaceType type) const
{
	return mFaces[type];
}
