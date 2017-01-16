#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
using namespace NSBullet;

NSDevilX::NSPhysicalSystem::NSBullet::CQuery::CQuery(IQueryImp * interfaceImp,CScene * scene)
	:TInterfaceObject<IQueryImp>(interfaceImp)
	,mScene(scene)
{
	getInterfaceImp()->addListener(this,IQueryImp::EMessage_Execute);
}

NSDevilX::NSPhysicalSystem::NSBullet::CQuery::~CQuery()
{}

Void NSDevilX::NSPhysicalSystem::NSBullet::CQuery::onMessage(IQueryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IQueryImp::EMessage_Execute:
		CSystem::getSingleton().update();
		_execute();
		break;
	}
}

NSDevilX::NSPhysicalSystem::NSBullet::CRayQuery::CRayQuery(IQueryImp * interfaceImp,CScene * scene)
	:CQuery(interfaceImp,scene)
{}

NSDevilX::NSPhysicalSystem::NSBullet::CRayQuery::~CRayQuery()
{}

btScalar NSDevilX::NSPhysicalSystem::NSBullet::CRayQuery::addSingleResult(btCollisionWorld::LocalRayResult & rayResult,bool normalInWorldSpace)
{
	if(getInterfaceImp()->getResultReceiver())
	{
		if(getInterfaceImp()->hasResultType(IEnum::EQueryResultType_HitPoint))
		{
			btVector3 hit_normal_world;
			if(normalInWorldSpace)
			{
				hit_normal_world=rayResult.m_hitNormalLocal;
			}
			else
			{
				///need to transform normal into worldspace
				hit_normal_world=m_collisionObject->getWorldTransform().getBasis()*rayResult.m_hitNormalLocal;
			}
			btVector3 hit_point_world;
			hit_point_world.setInterpolate3(btVector3(static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getOrigin().x,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getOrigin().y,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getOrigin().z)
				,btVector3(static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getDirection().x,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getDirection().y,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getDirection().z)*1000000.0f
				,rayResult.m_hitFraction);
			getInterfaceImp()->getResultReceiver()->addHitPoint(CFloat3(hit_point_world.x(),hit_point_world.y(),hit_point_world.z()),CFloat3(hit_normal_world.x(),hit_normal_world.y(),hit_normal_world.z()));
		}
		if(getInterfaceImp()->hasResultType(IEnum::EQueryResultType_HitSubEntity))
		{
			CEntity * entity=static_cast<CEntity*>(CSystem::getSingleton().getInstanceByInternal(rayResult.m_collisionObject));
			ISubEntity * sub_entity=entity->getInterfaceImp()->getSubEntity(entity->getInterfaceImp()->getMesh()->getSubMesh(static_cast<UInt32>(rayResult.m_localShapeInfo->m_shapePart)));
			getInterfaceImp()->getResultReceiver()->addHitSubEntity(sub_entity);
		}
	}
	return 0;
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CRayQuery::_execute()
{
	mScene->getInternal()->rayTest(btVector3(static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getOrigin().x,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getOrigin().y,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getOrigin().z)
		,btVector3(static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getDirection().x,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getDirection().y,static_cast<IRayQueryImp*>(getInterfaceImp())->getRay().getDirection().z)*1000000.0f
		,*this);
}
