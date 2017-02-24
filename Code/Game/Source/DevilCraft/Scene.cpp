#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSDevilCraft;

NSDevilX::NSDevilCraft::CScene::CScene(const String & name)
	:mRenderScene(nullptr)
	,mPhysicalScene(nullptr)
{
	mRenderScene=NSRenderSystem::getSystem()->createScene(name,NSRenderSystem::IEnum::ESceneManagerAlgorithm_Simple);
	mPhysicalScene=NSPhysicalSystem::getSystem()->createScene(name);
}

NSDevilX::NSDevilCraft::CScene::~CScene()
{
	NSRenderSystem::getSystem()->destroyScene(mRenderScene);
	NSPhysicalSystem::getSystem()->destroyScene(mPhysicalScene);
}

Void NSDevilX::NSDevilCraft::CScene::preUpdate()
{
	return Void();
}

Void NSDevilX::NSDevilCraft::CScene::update()
{
	return Void();
}
