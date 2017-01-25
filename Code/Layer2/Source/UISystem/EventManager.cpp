#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;
NSDevilX::NSUISystem::CEventManager::CEventManager()
{}

NSDevilX::NSUISystem::CEventManager::~CEventManager()
{}

Void NSDevilX::NSUISystem::CEventManager::addEventWindow(IEventWindowImp * window)
{
	mEventWindows.push_back(window);
}

Void NSDevilX::NSUISystem::CEventManager::removeEventWindow(IEventWindowImp * window)
{
	mEventWindows.erase(std::find(mEventWindows.begin(),mEventWindows.end(),window));
}

Void NSDevilX::NSUISystem::CEventManager::routeEvent(IEvent * e)
{
	const auto event_aabb=DirectX::BoundingBox(CFloat3(e->queryInterface_IElement()->getPosition()+CFloat3(e->queryInterface_IElement()->getSize().x,e->queryInterface_IElement()->getSize().y,0.0f)*0.5f),CFloat3(CFloat3(e->queryInterface_IElement()->getSize().x,e->queryInterface_IElement()->getSize().y,0.0f)*0.5f));
	for(auto window:mEventWindows)
	{
		const auto window_aabb=DirectX::BoundingBox(CFloat3(window->queryInterface_IElement()->getPosition()+CFloat3(window->queryInterface_IElement()->getSize().x,window->queryInterface_IElement()->getSize().y,0.0f)*0.5f),CFloat3(CFloat3(window->queryInterface_IElement()->getSize().x,window->queryInterface_IElement()->getSize().y,0.0f)*0.5f));
		if(event_aabb.Intersects(window_aabb))
		{
			window->notify(e);
		}
	}
}
