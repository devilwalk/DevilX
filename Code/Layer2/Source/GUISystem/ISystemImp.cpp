#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::ISystem * NSDevilX::NSGUISystem::getSystem()
{
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSGUISystem::ISystemImp::ISystemImp()
	:mWindow(nullptr)
{}

NSDevilX::NSGUISystem::ISystemImp::~ISystemImp()
{
}

Void NSDevilX::NSGUISystem::ISystemImp::initialize(CWindow * window)
{
	assert(!getWindow());
	mWindow=window;
}

IScene * NSDevilX::NSGUISystem::ISystemImp::createScene(NSRenderSystem::IViewport * viewport)
{
	if(mScenes.has(viewport))
		return nullptr;
	auto scene=DEVILX_NEW ISceneImp(viewport);
	mScenes.add(viewport,scene);
	return scene;
}

IScene * NSDevilX::NSGUISystem::ISystemImp::getScene(NSRenderSystem::IViewport * viewport) const
{
	return mScenes.get(viewport);
}

Void NSDevilX::NSGUISystem::ISystemImp::destroyScene(IScene * scene)
{
	return mScenes.destroy(scene->getRenderViewport());
}

Void NSDevilX::NSGUISystem::ISystemImp::update()
{
	for(auto const & pair:mScenes)
	{
		pair.second->update();
	}
	notify(EMessage_Update);
}

Void NSDevilX::NSGUISystem::ISystemImp::shutdown()
{
	NSUISystem::getSystem()->shutdown();
	DEVILX_DELETE(this);
}