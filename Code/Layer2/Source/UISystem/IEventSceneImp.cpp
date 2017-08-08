#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IEventSceneImp::IEventSceneImp(const String & name)
	:mName(name)
{
}

NSDevilX::NSUISystem::IEventSceneImp::~IEventSceneImp()
{
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
	mOrderedWindows[ret->queryInterface_IElement()->getDerivedOrder()].insert(ret);
	static_cast<IElementImp*>(ret->queryInterface_IElement())->addListener(this,IElementImp::EMessage_BeginDerivedOrderChange);
	static_cast<IElementImp*>(ret->queryInterface_IElement())->addListener(this,IElementImp::EMessage_EndDerivedOrderChange);
	return ret;
}

IEventWindow * NSDevilX::NSUISystem::IEventSceneImp::getWindow(const String & name) const
{
	return mWindows.get(name);
}

Void NSDevilX::NSUISystem::IEventSceneImp::destroyWindow(IEventWindow * window)
{
	mOrderedWindows[window->queryInterface_IElement()->getDerivedOrder()].erase(static_cast<IEventWindowImp*>(window));
	mWindows.destroy(window->queryInterface_IElement()->getName());
}

Boolean NSDevilX::NSUISystem::IEventSceneImp::route(IEvent * e)
{
	TVector<IEventWindowImp*> ordered_notify_windows;
	const auto event_aabb=DirectX::BoundingBox(CFloat3(e->queryInterface_IElement()->getDerivedPosition()+CFloat3(e->queryInterface_IElement()->getDerivedSize().x,e->queryInterface_IElement()->getDerivedSize().y,0.0f)*0.5f),CFloat3(CFloat3(e->queryInterface_IElement()->getDerivedSize().x,e->queryInterface_IElement()->getDerivedSize().y,0.0f)*0.5f));
	for(auto const & windows:mOrderedWindows)
	{
		for(auto window:windows.second)
		{
			if(window->queryInterface_IElement()->getEnable())
			{
				const auto window_aabb=DirectX::BoundingBox(CFloat3(window->queryInterface_IElement()->getDerivedPosition()+CFloat3(window->queryInterface_IElement()->getDerivedSize().x,window->queryInterface_IElement()->getDerivedSize().y,0.0f)*0.5f),CFloat3(CFloat3(window->queryInterface_IElement()->getDerivedSize().x,window->queryInterface_IElement()->getDerivedSize().y,0.0f)*0.5f));
				if(event_aabb.Intersects(window_aabb))
				{
					ordered_notify_windows.push_back(window);
				}
			}
		}
	}
	for(auto window:ordered_notify_windows)
		window->notify(e);
	return !ordered_notify_windows.empty();
}

Void NSDevilX::NSUISystem::IEventSceneImp::onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IElementImp::EMessage_BeginDerivedOrderChange:
		mOrderedWindows[notifier->getDerivedOrder()].erase(notifier->getUserPointer<IEventWindowImp>(0));
		break;
	case IElementImp::EMessage_EndDerivedOrderChange:
		mOrderedWindows[notifier->getDerivedOrder()].insert(notifier->getUserPointer<IEventWindowImp>(0));
		break;
	}
}
