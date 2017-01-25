#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::ISystem * NSDevilX::NSUISystem::getSystem()
{
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSUISystem::ISystemImp::ISystemImp()
{
}

NSDevilX::NSUISystem::ISystemImp::~ISystemImp()
{
}

IEventScene * NSDevilX::NSUISystem::ISystemImp::createEventScene(const String & name)
{
	if(mEventScenes.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IEventSceneImp(name);
	mEventScenes.add(name,ret);
	return ret;
}

IEventScene * NSDevilX::NSUISystem::ISystemImp::getEventScene(const String & name) const
{
	return mEventScenes.get(name);
}

Void NSDevilX::NSUISystem::ISystemImp::destroyEventScene(IEventScene * scene)
{
	mEventScenes.destroy(scene->getName());
}

IGraphicScene * NSDevilX::NSUISystem::ISystemImp::createGraphicScene(NSRenderSystem::IViewport * viewport)
{
	if(mGraphicScenes.has(viewport))
		return nullptr;
	auto ret=DEVILX_NEW IGraphicSceneImp(viewport);
	mGraphicScenes.add(viewport,ret);
	return ret;
}

IGraphicScene * NSDevilX::NSUISystem::ISystemImp::getGraphicScene(NSRenderSystem::IViewport * viewport) const
{
	return mGraphicScenes.get(viewport);
}

Void NSDevilX::NSUISystem::ISystemImp::destroyGraphicScene(IGraphicScene * scene)
{
	mGraphicScenes.destroy(scene->getRenderViewport());
}