#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
using namespace NSBullet;

NSDevilX::NSPhysicalSystem::NSBullet::CEntity::CEntity(IEntityImp * interfaceImp,CScene * scene)
	:TInterfaceObject<IEntityImp>(interfaceImp)
	,mScene(scene)
	,mMessageReceiver_ITransformerImp(this)
	,mNeedUpdateTransform(False)
	,mNeedRebuild(False)
{
	setInternal(new btCollisionObject);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityImp>*>(this),IEntityImp::EMessage_BeginMeshChange,False);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityImp>*>(this),IEntityImp::EMessage_EndMeshChange,False);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityImp>*>(this),IEntityImp::EMessage_BeginTransformerChange,False);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityImp>*>(this),IEntityImp::EMessage_EndTransformerChange,False);
}

NSDevilX::NSPhysicalSystem::NSBullet::CEntity::~CEntity()
{
	if(getInternal())
	{
		if(getInternal()->getCollisionShape())
			delete static_cast<btScaledBvhTriangleMeshShape*>(getInternal()->getCollisionShape())->getChildShape();
		delete getInternal()->getCollisionShape();
		delete getInternal();
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::update()
{
	_rebuild();
	_updateTransform();
}

void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::onMessage(IEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IEntityImp::EMessage_BeginMeshChange:
		if(getInterfaceImp()->getMesh())
		{
			CMesh * mesh=CSystem::getSingleton().getResourceManager()->getMesh(static_cast<IMeshImp*>(getInterfaceImp()->getMesh()));
			mesh->removeListener(static_cast<TMessageReceiver<CMesh>*>(this),CMesh::EMessage_EndRebuild);
		}
		break;
	case IEntityImp::EMessage_EndMeshChange:
		_needRebuild();
		if(getInterfaceImp()->getMesh())
		{
			CMesh * mesh=CSystem::getSingleton().getResourceManager()->getMesh(static_cast<IMeshImp*>(getInterfaceImp()->getMesh()));
			mesh->addListener(static_cast<TMessageReceiver<CMesh>*>(this),CMesh::EMessage_EndRebuild,False);
		}
		break;
	case IEntityImp::EMessage_BeginTransformerChange:
		static_cast<ITransformerImp*>(getInterfaceImp()->getTransformer())->removeListener(&mMessageReceiver_ITransformerImp,ITransformerImp::EMessage_EndOrientationChange);
		static_cast<ITransformerImp*>(getInterfaceImp()->getTransformer())->removeListener(&mMessageReceiver_ITransformerImp,ITransformerImp::EMessage_EndPositionChange);
		static_cast<ITransformerImp*>(getInterfaceImp()->getTransformer())->removeListener(&mMessageReceiver_ITransformerImp,ITransformerImp::EMessage_EndScaleChange);
		break;
	case IEntityImp::EMessage_EndTransformerChange:
		_needUpdateTransform();
		static_cast<ITransformerImp*>(getInterfaceImp()->getTransformer())->addListener(&mMessageReceiver_ITransformerImp,ITransformerImp::EMessage_EndOrientationChange);
		static_cast<ITransformerImp*>(getInterfaceImp()->getTransformer())->addListener(&mMessageReceiver_ITransformerImp,ITransformerImp::EMessage_EndPositionChange);
		static_cast<ITransformerImp*>(getInterfaceImp()->getTransformer())->addListener(&mMessageReceiver_ITransformerImp,ITransformerImp::EMessage_EndScaleChange);
		break;
	}
}

void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::onMessage(CMesh * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CMesh::EMessage_EndRebuild:
		_needRebuild();
		break;
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::_needRebuild()
{
	if(!mNeedRebuild)
	{
		if(getInternal()->getCollisionShape())
		{
			mScene->getInternal()->removeCollisionObject(getInternal());
			delete static_cast<btScaledBvhTriangleMeshShape*>(getInternal()->getCollisionShape())->getChildShape();
			delete getInternal()->getCollisionShape();
			getInternal()->setCollisionShape(nullptr);
		}
		if(getInterfaceImp()->getMesh())
		{
			mNeedRebuild=True;
		}
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::_needUpdateTransform()
{
	if(!mNeedUpdateTransform)
	{
		if(mNeedRebuild
			||getInterfaceImp()->getMesh()
			)
		{
			mNeedUpdateTransform=True;
		}
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::_rebuild()
{
	if(mNeedRebuild)
	{
		CMesh * mesh=CSystem::getSingleton().getResourceManager()->getMesh(static_cast<IMeshImp*>(getInterfaceImp()->getMesh()));
		getInternal()->setCollisionShape(new btScaledBvhTriangleMeshShape(new btBvhTriangleMeshShape(mesh->getInternal(),true),btVector3(1.0f,1.0f,1.0f)));
		mScene->getInternal()->addCollisionObject(getInternal());
		mNeedRebuild=False;
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::_updateTransform()
{
	if(mNeedUpdateTransform)
	{
		btTransform trans(btQuaternion(getInterfaceImp()->getTransformer()->getOrientation().x,getInterfaceImp()->getTransformer()->getOrientation().y,getInterfaceImp()->getTransformer()->getOrientation().z,getInterfaceImp()->getTransformer()->getOrientation().w)
			,btVector3(getInterfaceImp()->getTransformer()->getPosition().x,getInterfaceImp()->getTransformer()->getPosition().y,getInterfaceImp()->getTransformer()->getPosition().z));
		getInternal()->setWorldTransform(trans);
		getInternal()->getCollisionShape()->setLocalScaling(btVector3(getInterfaceImp()->getTransformer()->getScale().x,getInterfaceImp()->getTransformer()->getScale().y,getInterfaceImp()->getTransformer()->getScale().z));
		mScene->getInternal()->updateSingleAabb(getInternal());
		mNeedUpdateTransform=False;
	}
}

void NSDevilX::NSPhysicalSystem::NSBullet::CEntity::SMessageReceiver_ITransformerImp::onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITransformerImp::EMessage_EndOrientationChange:
	case ITransformerImp::EMessage_EndPositionChange:
	case ITransformerImp::EMessage_EndScaleChange:
		mEntity->_needUpdateTransform();
		break;
	}
}
