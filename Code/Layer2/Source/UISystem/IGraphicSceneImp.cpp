#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IGraphicSceneImp::IGraphicSceneImp(NSRenderSystem::IViewport * viewport)
	:mViewport(viewport)
{
}

NSDevilX::NSUISystem::IGraphicSceneImp::~IGraphicSceneImp()
{
}

NSRenderSystem::IViewport * NSDevilX::NSUISystem::IGraphicSceneImp::getRenderViewport() const
{
	return mViewport;
}

IGraphicWindow * NSDevilX::NSUISystem::IGraphicSceneImp::createWindow(const String & name)
{
	if(mWindows.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IGraphicWindowImp(name,this);
	mWindows.add(name,ret);
	return ret;
}

IGraphicWindow * NSDevilX::NSUISystem::IGraphicSceneImp::getWindow(const String & name) const
{
	return mWindows.get(name);
}

Void NSDevilX::NSUISystem::IGraphicSceneImp::destroyWindow(IGraphicWindow * window)
{
	mWindows.destroy(window->queryInterface_IElement()->getName());
}
