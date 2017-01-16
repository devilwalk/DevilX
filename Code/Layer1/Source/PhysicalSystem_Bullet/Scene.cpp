#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
using namespace NSBullet;

NSDevilX::NSPhysicalSystem::NSBullet::CScene::CScene(ISceneImp * interfaceImp)
	:TInterfaceObject<ISceneImp>(interfaceImp)
{
	bt32BitAxisSweep3 * broadphase=new bt32BitAxisSweep3(btVector3(-100.0f,-100.0f,-100.0f),btVector3(100.0f,100.0f,100.0f));
	btDefaultCollisionConfiguration * config=new btDefaultCollisionConfiguration;
	setInternal(new btCollisionWorld(new btCollisionDispatcher(config),broadphase,config));
	getInterfaceImp()->addListener(this,ISceneImp::EMessage_EndEntityCreate,False);
	getInterfaceImp()->addListener(this,ISceneImp::EMessage_BeginEntityDestroy,False);
	getInterfaceImp()->addListener(this,ISceneImp::EMessage_EndQueryCreate,False);
	getInterfaceImp()->addListener(this,ISceneImp::EMessage_BeginQueryDestroy,False);
}

NSDevilX::NSPhysicalSystem::NSBullet::CScene::~CScene()
{
	mQuerys.destroyAll();
	auto broadphase=getInternal()->getBroadphase();
	auto config=static_cast<btCollisionDispatcher*>(getInternal()->getDispatcher())->getCollisionConfiguration();
	auto dispatcher=getInternal()->getDispatcher();
	delete getInternal();
	mEntitys.destroyAll();
	delete broadphase;
	delete config;
	delete dispatcher;
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CScene::update()
{
	for(auto const & entity_pairs:mEntitys)
	{
		entity_pairs.second->update();
	}
	getInternal()->computeOverlappingPairs();
}

void NSDevilX::NSPhysicalSystem::NSBullet::CScene::onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneImp::EMessage_EndEntityCreate:
		mEntitys[static_cast<IEntityImp*>(data)]=DEVILX_NEW CEntity(static_cast<IEntityImp*>(data),this);
		break;
	case ISceneImp::EMessage_BeginEntityDestroy:
		getInternal()->removeCollisionObject(mEntitys[static_cast<IEntityImp*>(data)]->getInternal());
		mEntitys.destroy(static_cast<IEntityImp*>(data));
		break;
	case ISceneImp::EMessage_EndQueryCreate:
		switch(static_cast<IQueryImp*>(data)->getType())
		{
		case IEnum::EQueryType_Ray:
			mQuerys[static_cast<IQueryImp*>(data)]=DEVILX_NEW CRayQuery(static_cast<IQueryImp*>(data),this);
			break;
		}
		break;
	case ISceneImp::EMessage_BeginQueryDestroy:
		mQuerys.destroy(static_cast<IQueryImp*>(data));
		break;
	}
}
