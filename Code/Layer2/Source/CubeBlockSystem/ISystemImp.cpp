#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockSystem;
NSDevilX::NSCubeBlockSystem::ISystem * NSDevilX::NSCubeBlockSystem::getSystem()
{
	return ISystemImp::getSingletonPtr();
}
NSDevilX::NSCubeBlockSystem::ISystemImp::ISystemImp()
	:mRenderableThreadPool(nullptr)
{
	mRenderableThreadPool=DEVILX_NEW CThreadPool(4);
}

NSDevilX::NSCubeBlockSystem::ISystemImp::~ISystemImp()
{}

Void NSDevilX::NSCubeBlockSystem::ISystemImp::update()
{
	for(auto scene:mScenes)
	{
		scene->update();
	}
}

IBlock * NSDevilX::NSCubeBlockSystem::ISystemImp::createBlock(const String & name)
{
	if(getBlock(name))
		return nullptr;
	auto ret=DEVILX_NEW IBlockImp(name);
	mBlocks.add(name,ret);
	return ret;
}

IBlock * NSDevilX::NSCubeBlockSystem::ISystemImp::getBlock(const String & name) const
{
	return mBlocks.get(name);
}

IScene * NSDevilX::NSCubeBlockSystem::ISystemImp::createScene(NSRenderSystem::IScene * renderScene)
{
	auto ret=DEVILX_NEW ISceneImp(renderScene);
	mScenes.insert(ret);
	return ret;
}

Void NSDevilX::NSCubeBlockSystem::ISystemImp::destroyScene(IScene * scene)
{
	mScenes.destroy(static_cast<ISceneImp*>(scene));
}

IRenderMaterial * NSDevilX::NSCubeBlockSystem::ISystemImp::createRenderMaterial(const String & name)
{
	if(getRenderMaterial(name))
		return nullptr;
	auto ret=DEVILX_NEW IRenderMaterialImp(name);
	mRenderMaterials.add(name,ret);
	return ret;
}

IRenderMaterial * NSDevilX::NSCubeBlockSystem::ISystemImp::getRenderMaterial(const String & name) const
{
	return mRenderMaterials.get(name);
}

Void NSDevilX::NSCubeBlockSystem::ISystemImp::destroyRenderMaterial(IRenderMaterial * material)
{
	mRenderMaterials.destroy(material->getName());
}
