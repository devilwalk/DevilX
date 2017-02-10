#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::ISystemImp::ISystemImp()
	:mResourceManager(nullptr)
	,mExit(False)
	,mFrameTimeInSecond(0.0f)
	,mFrameIndex(0)
{
	mResourceManager=DEVILX_NEW IResourceManagerImp;
}

NSDevilX::NSRenderSystem::ISystemImp::~ISystemImp()
{
	mExit=True;
	notify(EMessage_Destruction);
	DEVILX_DELETE(mResourceManager);
}

Void NSDevilX::NSRenderSystem::ISystemImp::shutdown()
{
	DEVILX_DELETE(this);
}

IResourceManager * NSDevilX::NSRenderSystem::ISystemImp::queryInterface_IResourceManager() const
{
	return mResourceManager;
}

Void NSDevilX::NSRenderSystem::ISystemImp::update()
{
	static auto last_time=clock();
	const auto current_time=clock();
	mFrameTimeInSecond=(current_time-last_time)*1.0f/CLOCKS_PER_SEC;
	last_time=current_time;
	notify(EMessage_Update);
	++mFrameIndex;
}

IWindow * NSDevilX::NSRenderSystem::ISystemImp::createWindow(VoidPtr windowHandle)
{
	if(mWindows.has(windowHandle))
		return nullptr;
	notify(EMessage_BeginWindowCreate);
	IWindowImp * ret=DEVILX_NEW IWindowImp(windowHandle);
	mWindows[windowHandle]=ret;
	notify(EMessage_EndWindowCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::ISystemImp::destroyWindow(IWindow * window)
{
	if(!mWindows.has(static_cast<IWindowImp*>(window)->getHandle()))
		return;
	notify(EMessage_BeginWindowDestroy,static_cast<IWindowImp*>(window));
	mWindows.destroy(static_cast<IWindowImp*>(window)->getHandle());
	notify(EMessage_EndWindowDestroy);
}

IWindow * NSDevilX::NSRenderSystem::ISystemImp::getWindow(VoidPtr windowHandle) const
{
	return mWindows.get(windowHandle);
}

IRenderableSurface * NSDevilX::NSRenderSystem::ISystemImp::createRenderableSurface(const String & name)
{
	if(mRenderableSurfaces.has(name))
		return nullptr;
	notify(EMessage_BeginRenderableSurfaceCreate);
	IRenderableSurfaceImp * ret=DEVILX_NEW IRenderableSurfaceImp(name);
	mRenderableSurfaces[name]=ret;
	notify(EMessage_EndRenderableSurfaceCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::ISystemImp::destroyRenderableSurface(IRenderableSurface * surface)
{
	if(!mRenderableSurfaces.has(static_cast<IRenderableSurfaceImp*>(surface)->getName()))
		return;
	notify(EMessage_BeginRenderableSurfaceDestroy,static_cast<IRenderableSurfaceImp*>(surface));
	mRenderableSurfaces.destroy(static_cast<IRenderableSurfaceImp*>(surface)->getName());
	notify(EMessage_EndRenderableSurfaceDestroy);
}

IRenderableSurface * NSDevilX::NSRenderSystem::ISystemImp::getRenderableSurface(const String & name) const
{
	return mRenderableSurfaces.get(name);
}

IScene * NSDevilX::NSRenderSystem::ISystemImp::createScene(const String & name,IEnum::ESceneManagerAlgorithm algorithm)
{
	if(mScenes.has(name))
		return nullptr;
	notify(EMessage_BeginSceneCreate);
	ISceneImp * ret=DEVILX_NEW ISceneImp(name,algorithm);
	mScenes[name]=ret;
	notify(EMessage_EndSceneCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::ISystemImp::destroyScene(IScene * scene)
{
	if(!mScenes.has(scene->getName()))
		return;
	notify(EMessage_BeginSceneDestroy,static_cast<ISceneImp*>(scene));
	mScenes.destroy(scene->getName());
	notify(EMessage_EndSceneDestroy);
}

IScene * NSDevilX::NSRenderSystem::ISystemImp::getScene(const String & name) const
{
	return mScenes.get(name);
}