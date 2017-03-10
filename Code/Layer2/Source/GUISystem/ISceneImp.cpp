#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::ISceneImp::ISceneImp(NSRenderSystem::IViewport * viewport)
	:mGraphicScene(nullptr)
{
	mGraphicScene=NSUISystem::getSystem()->createGraphicScene(viewport);
}

NSDevilX::NSGUISystem::ISceneImp::~ISceneImp()
{
	NSUISystem::getSystem()->destroyGraphicScene(getGraphicScene());
}

NSRenderSystem::IViewport * NSDevilX::NSGUISystem::ISceneImp::getRenderViewport() const
{
	return getGraphicScene()->getRenderViewport();
}

IWindow * NSDevilX::NSGUISystem::ISceneImp::createWindow(const String & name)
{
	if(mWindows.has(name))
		return nullptr;
	auto window=DEVILX_NEW IWindowImp(name,this);
	mWindows.add(name,window);
	return window;
}

IWindow * NSDevilX::NSGUISystem::ISceneImp::getWindow(const String & name) const
{
	return mWindows.get(name);
}

Void NSDevilX::NSGUISystem::ISceneImp::destroyWindow(IWindow * window)
{
	mWindows.destroy(window->queryInterface_IControl()->queryInterface_IElement()->getName());
}
