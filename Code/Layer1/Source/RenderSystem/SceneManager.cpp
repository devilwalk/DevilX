#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::CSceneManager::CSceneManager()
{
}

NSDevilX::NSRenderSystem::CSceneManager::~CSceneManager()
{}

NSDevilX::NSRenderSystem::CSimpleSceneManager::CSimpleSceneManager()
	:CSceneManager()
{}

NSDevilX::NSRenderSystem::CSimpleSceneManager::~CSimpleSceneManager()
{}

IEnum::ESceneManagerAlgorithm NSDevilX::NSRenderSystem::CSimpleSceneManager::getAlgorithm() const
{
	return IEnum::ESceneManagerAlgorithm_Simple;
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::findVisibleObjects(const CPlaneBoundedVolume & bound,TVector(CVisibleArea*) & visibleObjects,UInt32 mask) const
{
	for(auto area:mElements)
	{
		if(area->hasMask(mask)&&(DirectX::DISJOINT!=bound.contains(area->getBoundingBox())))
		{
			visibleObjects.push_back(area);
		}
	}
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::findVisibleObjects(const DirectX::BoundingSphere & bound,TVector(CVisibleArea*)& visibleObjects,UInt32 mask) const
{
	for(auto area:mElements)
	{
		if(area->hasMask(mask)&&bound.Intersects(area->getBoundingBox()))
		{
			visibleObjects.push_back(area);
		}
	}
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::addVisibleArea(CVisibleArea * area)
{
	mElements.insert(area);
}

Void NSDevilX::NSRenderSystem::CSimpleSceneManager::removeVisibleAra(CVisibleArea * area)
{
	mElements.erase(area);
}
