#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;
NSDevilX::Boolean install(NSDevilX::NSCubeBlockWorld::IWorld * world,NSCubeBlockSystem::ISystem * system)
{
	assert(NSCubeBlockWorld::CModule::getSingletonPtr()==nullptr);
	DEVILX_NEW NSCubeBlockWorld::CModule(world,system);
	return true;
}

NSDevilX::Void dllUnload()
{
	DEVILX_DELETE(NSCubeBlockWorld::CModule::getSingletonPtr());
}

NSDevilX::NSCubeBlockWorld::CModule::CModule(NSDevilX::NSCubeBlockWorld::IWorld * world,NSCubeBlockSystem::ISystem * system)
	:mWorld(world)
	,mSystem(system)
{
	getWorld()->registerTerrainGenerator(DEVILX_NEW CSimpleTerrainGenertor());
}

NSDevilX::NSCubeBlockWorld::CModule::~CModule()
{
	DEVILX_DELETE(CSimpleTerrainGenertor::getSingletonPtr());
}
