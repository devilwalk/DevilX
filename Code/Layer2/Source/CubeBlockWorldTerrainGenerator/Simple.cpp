#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::CSimpleTerrainGeneratorInstance(CSimpleTerrainGenertor * generator,ISceneManager * sceneManager)
	:CTerrainGeneratorInstance(generator,sceneManager)
	,mBlock(nullptr)
{
	mBlock=CModule::getSingleton().getSystem()->getBlock("Simple");
}

NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::~CSimpleTerrainGeneratorInstance()
{}

NSCubeBlockSystem::IBlock * NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::generateBlockMT(const CInt3 & position)
{
	return mBlock;
}

UInt32 NSDevilX::NSCubeBlockWorld::CSimpleTerrainGeneratorInstance::generateChunkMT(const CInt3 & position,OUT CInt3 * blockPositions)
{
	CInt3 base_pos=position*mSceneManager->getChunkSize();
	if(blockPositions)
	{
		UInt32 index=0;
		for(UInt32 x=0;x<mSceneManager->getChunkSize().x;++x)
		{
			for(UInt32 y=0;y<mSceneManager->getChunkSize().y;++y)
			{
				if(base_pos.y+y>1)
					break;
				for(UInt32 z=0;z<mSceneManager->getChunkSize().z;++z)
				{
					blockPositions[index]=base_pos+CInt3(x,y,z);
					++index;
				}
			}
		}
		return index;
	}
	else
	{
		UInt32 y=0;
		for(;y<mSceneManager->getChunkSize().y;++y)
		{
			if(base_pos.y+y>1)
				break;
		}
		return mSceneManager->getChunkSize().x*y*mSceneManager->getChunkSize().z;
	}
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
