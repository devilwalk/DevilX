#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::CSimpleTerrainGeneratorInstance(CSimpleTerrainGenertor * generator,ISceneManager * sceneManager)
	:CTerrainGeneratorInstance(generator,sceneManager)
{}

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::~CSimpleTerrainGeneratorInstance()
{}

NSCubeBlockSystem::IBlock * NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::generateBlock(DirectX::XMVECTOR positionVec)
{
	return CModule::getSingleton().getSystem()->getBlock("Simple");
}

Boolean NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::generateChunk(DirectX::XMVECTOR positionVec)
{
	const DirectX::XMVECTOR chunk_size_vec=mSceneManager->getChunkSize();
	CSInt3 start=DirectX::XMVectorMax(positionVec*chunk_size_vec,mSceneManager->getRange().getMin());
	CSInt3 end=DirectX::XMVectorMin(start+chunk_size_vec-CSInt3::sOne,mSceneManager->getRange().getMax());
	mSceneManager->getScene()->setBlockMT(CRange3I(start,end),CModule::getSingleton().getSystem()->getBlock("Simple"));
	return true;
}

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGenertor::CSimpleTerrainGenertor()
	:mName("Simple")
{
	auto block=CModule::getSingleton().getSystem()->createBlock("Simple");
	for(auto face_index=0;face_index<6;++face_index)
	{
		auto face=block->getFace((NSCubeBlockSystem::IEnum::EBlockFaceType)face_index);
	}
}

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGenertor::~CSimpleTerrainGenertor()
{}

const String & NSDevilX::NSCubeBlockWorld::CSimpleTerrainGenertor::getName() const
{
	// TODO: insert return statement here
	return mName;
}

ITerrainGeneratorInstance * NSDevilX::NSCubeBlockWorld::CSimpleTerrainGenertor::createInstance(ISceneManager * sceneManager)
{
	return DEVILX_NEW CSimpleTerrainGeneratorInstance(this,sceneManager);
}

Void NSDevilX::NSCubeBlockWorld::CSimpleTerrainGenertor::destroyInstance(ITerrainGeneratorInstance * instance)
{
	DEVILX_DELETE(static_cast<CSimpleTerrainGeneratorInstance*>(instance));
}
