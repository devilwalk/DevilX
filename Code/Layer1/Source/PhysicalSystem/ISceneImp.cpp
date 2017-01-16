#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;

NSDevilX::NSPhysicalSystem::ISceneImp::ISceneImp(const String & name)
	:mName(name)
{}

NSDevilX::NSPhysicalSystem::ISceneImp::~ISceneImp()
{
	if(!ISystemImp::getSingleton().isExit())
	{
		notify(EMessage_BeginDestruction);
		mEntitys.destroyAll();
		mQuerys.destroyAll();
		notify(EMessage_EndDestruction);
	}
}

const String & NSDevilX::NSPhysicalSystem::ISceneImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IEntity * NSDevilX::NSPhysicalSystem::ISceneImp::createEntity(const String & name)
{
	notify(EMessage_BeginEntityCreate);
	IEntityImp * entity=DEVILX_NEW IEntityImp(name,this);
	mEntitys[name]=entity;
	notify(EMessage_EndEntityCreate,entity);
	return entity;
}

Void NSDevilX::NSPhysicalSystem::ISceneImp::destroyEntity(IEntity * entity)
{
	notify(EMessage_BeginEntityDestroy,static_cast<IEntityImp*>(entity));
	mEntitys.destroy(entity->getName());
	notify(EMessage_EndEntityDestroy);
}

IEntity * NSDevilX::NSPhysicalSystem::ISceneImp::getEntity(const String & name) const
{
	return mEntitys.get(name);
}

IQuery * NSDevilX::NSPhysicalSystem::ISceneImp::createQuery(const String & name,IEnum::EQueryType type)
{
	IQueryImp * ret=nullptr;
	notify(EMessage_BeginQueryCreate);
	switch(type)
	{
	case IEnum::EQueryType_Ray:
		ret=DEVILX_NEW IRayQueryImp(name,this);
	}
	if(ret)
		mQuerys[name]=ret;
	notify(EMessage_EndQueryCreate,ret);
	return ret;
}

Void NSDevilX::NSPhysicalSystem::ISceneImp::destroyQuery(IQuery * query)
{
	notify(EMessage_BeginQueryDestroy,static_cast<IQueryImp*>(query));
	mQuerys.destroy(query->getName());
	notify(EMessage_EndQueryDestroy,static_cast<IQueryImp*>(query));
}

IQuery * NSDevilX::NSPhysicalSystem::ISceneImp::getQuery(const String & name) const
{
	return mQuerys.get(name);
}
