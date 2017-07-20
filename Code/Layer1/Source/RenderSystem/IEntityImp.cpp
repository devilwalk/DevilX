#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IEntityImp::IEntityImp(const String & name,ISceneImp * scene)
	:mSceneElement(nullptr)
{
	mSceneElement=DEVILX_NEW ISceneElementImp(name,scene,this,ISceneElementImp::EContainerObjectType_Entity);
}

NSDevilX::NSRenderSystem::IEntityImp::~IEntityImp()
{
	DEVILX_DELETE(mSceneElement);
}

ISceneElement * NSDevilX::NSRenderSystem::IEntityImp::queryInterface_ISceneElement() const
{
	return mSceneElement;
}

ISubEntity * NSDevilX::NSRenderSystem::IEntityImp::createSubEntity(const String & name)
{
	if(mSubEntities.has(name))
		return nullptr;
	notify(EMessage_BeginSubEntityCreate);
	ISubEntityImp * sub_entity=DEVILX_NEW ISubEntityImp(name,this);
	mSubEntities.add(name,sub_entity);
	notify(EMessage_EndSubEntityCreate,sub_entity);
	return sub_entity;
}

ISubEntity * NSDevilX::NSRenderSystem::IEntityImp::getSubEntity(const String & name) const
{
	return mSubEntities.get(name);
}

ISubEntity * NSDevilX::NSRenderSystem::IEntityImp::getSubEntity(UInt32 index) const
{
	return mSubEntities.get(index);
}

UInt32 NSDevilX::NSRenderSystem::IEntityImp::getSubEntityCount() const
{
	return static_cast<UInt32>(mSubEntities.size());
}

Void NSDevilX::NSRenderSystem::IEntityImp::destroySubEntity(ISubEntity * subEntity)
{
	if((!subEntity)
		||(!mSubEntities.has(subEntity->getName()))
		)
		return;
	notify(EMessage_BeginSubEntityDestroy,static_cast<ISubEntityImp*>(subEntity));
	mSubEntities.destroy(subEntity->getName());
	notify(EMessage_EndSubEntityDestroy,static_cast<ISubEntityImp*>(subEntity));
}
