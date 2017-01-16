#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
NSDevilX::NSPhysicalSystem::ISystemImp::ISystemImp()
	:mResourceManager(nullptr)
	,mExit(False)
{
	mResourceManager=DEVILX_NEW IResourceManagerImp;
}

NSDevilX::NSPhysicalSystem::ISystemImp::~ISystemImp()
{
	mExit=True;
	notify(EMessage_Destruction);
	DEVILX_DELETE(mResourceManager);
}

IResourceManager * NSDevilX::NSPhysicalSystem::ISystemImp::queryInterface_IResourceManager() const
{
	return mResourceManager;
}

Void NSDevilX::NSPhysicalSystem::ISystemImp::shutdown()
{
	DEVILX_DELETE(this);
}

IScene * NSDevilX::NSPhysicalSystem::ISystemImp::createScene(const String & name)
{
	notify(EMessage_BeginSceneCreate);
	ISceneImp * scene=DEVILX_NEW ISceneImp(name);
	mScenes[name]=scene;
	notify(EMessage_EndSceneCreate,scene);
	return scene;
}

Void NSDevilX::NSPhysicalSystem::ISystemImp::destroyScene(IScene * scene)
{
	notify(EMessage_BeginSceneDestroy,static_cast<ISceneImp*>(scene));
	mScenes.destroy(scene->getName());
	notify(EMessage_BeginSceneCreate);
}

IScene * NSDevilX::NSPhysicalSystem::ISystemImp::getScene(const String & name) const
{
	return mScenes.get(name);
}
