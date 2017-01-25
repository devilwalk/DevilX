#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IEventSceneImp::IEventSceneImp(const String & name)
	:mName(name)
	,mManager(nullptr)
{
	mManager=DEVILX_NEW CEventManager;
}

NSDevilX::NSUISystem::IEventSceneImp::~IEventSceneImp()
{
	DEVILX_DELETE(mManager);
}

const String & NSDevilX::NSUISystem::IEventSceneImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

IEventWindow * NSDevilX::NSUISystem::IEventSceneImp::createWindow(const String & name)
{
	if(mWindows.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IEventWindowImp(name);
	mWindows.add(name,ret);
	mManager->addEventWindow(ret);
	return ret;
}

IEventWindow * NSDevilX::NSUISystem::IEventSceneImp::getWindow(const String & name) const
{
	return mWindows.get(name);
}

Void NSDevilX::NSUISystem::IEventSceneImp::destroyWindow(IEventWindow * window)
{
	mManager->removeEventWindow(static_cast<IEventWindowImp*>(window));
	mWindows.destroy(window->queryInterface_IElement()->getName());
}

Void NSDevilX::NSUISystem::IEventSceneImp::route(IEvent * eve)
{
	mManager->routeEvent(eve);
}
