#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;
NSDevilX::NSCubeBlockWorld::CTerrainGeneratorInstance::CTerrainGeneratorInstance(ITerrainGenerator * generator,ISceneManager * sceneManager)
	:mGenerator(generator)
	,mSceneManager(sceneManager)
{}

NSDevilX::NSCubeBlockWorld::CTerrainGeneratorInstance::~CTerrainGeneratorInstance()
{}

ITerrainGenerator * NSDevilX::NSCubeBlockWorld::CTerrainGeneratorInstance::getGenerator() const
{
	return mGenerator;
}

ISceneManager * NSDevilX::NSCubeBlockWorld::CTerrainGeneratorInstance::getSceneManager() const
{
	return mSceneManager;
}
