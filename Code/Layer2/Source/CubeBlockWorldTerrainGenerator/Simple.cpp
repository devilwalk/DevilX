#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::CSimpleTerrainGeneratorInstance(CSimpleTerrainGenertor * generator,ISceneManager * sceneManager)
	:CTerrainGeneratorInstance(generator,sceneManager)
{
}

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::~CSimpleTerrainGeneratorInstance()
{}

NSCubeBlockSystem::IBlock * NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::generateBlock(const CInt3 & position)
{
	return CModule::getSingleton().getSystem()->getBlock("Simple");
}

Boolean NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::generateChunk(const CInt3 & position)
{
	const DirectX::XMVECTOR chunk_size_vec=mSceneManager->getChunkSize();
	CInt3 start=DirectX::XMVectorMax(position*chunk_size_vec,mSceneManager->getRange().getMin());
	CInt3 end=DirectX::XMVectorMin(start+chunk_size_vec-CInt3::sOne,mSceneManager->getRange().getMax());
	mSceneManager->getScene()->setBlockMT(CRange3I(start,end),CModule::getSingleton().getSystem()->getBlock("Simple"));
	return true;
}

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGenertor::CSimpleTerrainGenertor()
	:mName("Simple")
{
	auto render_material=CModule::getSingleton().getSystem()->createRenderMaterial("DefaultWhite");
	render_material->setColour(CFloatRGB::sWhite);
	auto block=CModule::getSingleton().getSystem()->createBlock("Simple");
	for(auto face_index=0;face_index<6;++face_index)
	{
		auto face=block->getFace((NSCubeBlockSystem::IEnum::EBlockFaceType)face_index);
		face->setRenderMaterial(render_material);
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
