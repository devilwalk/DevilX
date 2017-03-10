#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

ISystem * NSDevilX::NSGUISystem::getSystem()
{
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSGUISystem::ISystemImp::ISystemImp()
{}

NSDevilX::NSGUISystem::ISystemImp::~ISystemImp()
{
}

Void NSDevilX::NSGUISystem::ISystemImp::setFontManager(CFontManager * manager)
{
	if(getFontManager()!=manager)
	{
		notify(EMessage_BeginFontManagerChange);
		mFontManager=manager;
		notify(EMessage_EndFontManagerChange);
	}
}

CFontManager * NSDevilX::NSGUISystem::ISystemImp::getFontManager() const
{
	return mFontManager;
}

Void NSDevilX::NSGUISystem::ISystemImp::setFontName(const String & fontName)
{
	if(getFontName()!=fontName)
	{
		notify(EMessage_BeginFontNameChange);
		mFontName=fontName;
		notify(EMessage_EndFontNameChange);
	}
}

const String & NSDevilX::NSGUISystem::ISystemImp::getFontName() const
{
	// TODO: 在此处插入 return 语句
	return mFontName;
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

Void NSDevilX::NSGUISystem::ISystemImp::shutdown()
{
	DEVILX_DELETE(this);
}
