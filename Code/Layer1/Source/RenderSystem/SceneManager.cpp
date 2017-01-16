#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::CSceneManager::CSceneManager(ISceneImp * scene)
	:mScene(scene)
{
	mScene->addListener(this,ISceneImp::EMessage_EndVisibleAreaCreate);
	mScene->addListener(this,ISceneImp::EMessage_BeginVisibleAreaDestroy);
}

NSDevilX::NSRenderSystem::CSceneManager::~CSceneManager()
{}

Void NSDevilX::NSRenderSystem::CSceneManager::onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneImp::EMessage_EndVisibleAreaCreate:
		_addElement(static_cast<IVisibleAreaImp*>(data));
		break;
	case ISceneImp::EMessage_BeginVisibleAreaDestroy:
		_removeElement(static_cast<IVisibleAreaImp*>(data));
		break;
	}
}

NSDevilX::NSRenderSystem::CSimpleSceneManager::CSimpleSceneManager(ISceneImp * scene)
	:CSceneManager(scene)
{}

NSDevilX::NSRenderSystem::CSimpleSceneManager::~CSimpleSceneManager()
{}

IEnum::ESceneManagerAlgorithm NSDevilX::NSRenderSystem::CSimpleSceneManager::getAlgorithm() const
{
	return IEnum::ESceneManagerAlgorithm_Simple;
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::findVisibleObjects(const CPlaneBoundedVolume & bound,TVector<ISceneElementImp*> & visibleObjects) const
{
	for(auto area:mElements)
	{
		if(DirectX::DISJOINT!=bound.contains(area->getWorldBoundingBox()))
		{
			for(auto obj:area->getAttachedObjects())
			{
				visibleObjects.push_back(obj);
			}
		}
	}
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::findVisibleObjects(const DirectX::BoundingSphere & bound,TVector<ISceneElementImp*>& visibleObjects) const
{
	for(auto area:mElements)
	{
		if(bound.Intersects(area->getWorldBoundingBox()))
		{
			for(auto obj:area->getAttachedObjects())
			{
				visibleObjects.push_back(obj);
			}
		}
	}
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::_addElement(IVisibleAreaImp * element)
{
	mElements.insert(element);
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::_removeElement(IVisibleAreaImp * element)
{
	mElements.erase(element);
}