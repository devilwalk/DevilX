#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
using namespace NSBullet;

NSDevilX::NSPhysicalSystem::NSBullet::CMesh::CMesh(IMeshImp * interfaceImp)
	:TInterfaceObject<IMeshImp>(interfaceImp)
	,mMessageReceiver_IGeometryImp(this)
	,mNeedRebuild(False)
{
	setInternal(new btTriangleIndexVertexArray);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMeshImp>*>(this),IMeshImp::EMessage_EndSubMeshCreate,False);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMeshImp>*>(this),IMeshImp::EMessage_BeginSubMeshDestroy,False);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMeshImp>*>(this),IMeshImp::EMessage_BeginGeometryChange,False);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMeshImp>*>(this),IMeshImp::EMessage_EndGeometryChange,False);
}

NSDevilX::NSPhysicalSystem::NSBullet::CMesh::~CMesh()
{
	delete getInternal();
}

void NSDevilX::NSPhysicalSystem::NSBullet::CMesh::onMessage(IMeshImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IMeshImp::EMessage_EndSubMeshCreate:
		_needRebuild();
		static_cast<ISubMeshImp*>(data)->addListener(static_cast<TMessageReceiver<ISubMeshImp>*>(this),ISubMeshImp::EMessage_EndIndexCountChange,False);
		static_cast<ISubMeshImp*>(data)->addListener(static_cast<TMessageReceiver<ISubMeshImp>*>(this),ISubMeshImp::EMessage_EndIndexStartChange,False);
		static_cast<ISubMeshImp*>(data)->addListener(static_cast<TMessageReceiver<ISubMeshImp>*>(this),ISubMeshImp::EMessage_EndVertexStartChange,False);
		break;
	case IMeshImp::EMessage_BeginSubMeshDestroy:
		_needRebuild();
		break;
	case IMeshImp::EMessage_BeginGeometryChange:
		if(notifier->getGeometry())
		{
			static_cast<IGeometryImp*>(notifier->getGeometry())->removeListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndIndexCountChange);
			static_cast<IGeometryImp*>(notifier->getGeometry())->removeListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndIndicesChange);
			static_cast<IGeometryImp*>(notifier->getGeometry())->removeListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndPositionsChange);
			static_cast<IGeometryImp*>(notifier->getGeometry())->removeListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndVertexCountChange);
		}
		break;
	case IMeshImp::EMessage_EndGeometryChange:
		_needRebuild();
		if(notifier->getGeometry())
		{
			static_cast<IGeometryImp*>(notifier->getGeometry())->addListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndIndexCountChange);
			static_cast<IGeometryImp*>(notifier->getGeometry())->addListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndIndicesChange);
			static_cast<IGeometryImp*>(notifier->getGeometry())->addListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndPositionsChange);
			static_cast<IGeometryImp*>(notifier->getGeometry())->addListener(&mMessageReceiver_IGeometryImp,IGeometryImp::EMessage_EndVertexCountChange);
		}
		break;
	}
}

void NSDevilX::NSPhysicalSystem::NSBullet::CMesh::onMessage(ISubMeshImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISubMeshImp::EMessage_EndIndexCountChange:
	case ISubMeshImp::EMessage_EndIndexStartChange:
	case ISubMeshImp::EMessage_EndVertexStartChange:
		_needRebuild();
		break;
	}
}

void NSDevilX::NSPhysicalSystem::NSBullet::CMesh::onMessage(CSystem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystem::EMessage_BeginUpdate:
		_rebuild();
		CSystem::getSingleton().removeListener(static_cast<TMessageReceiver<CSystem>*>(this),CSystem::EMessage_BeginUpdate);
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CMesh::_needRebuild()
{
	getInternal()->getIndexedMeshArray().clear();
	const bool need_rebuild=(getInterfaceImp()->getGeometry()!=nullptr)
		&&getInterfaceImp()->getGeometry()->getVertexCount()
		&&getInterfaceImp()->getGeometry()->getIndexCount()
		&&getInterfaceImp()->getGeometry()->getPositions()
		&&getInterfaceImp()->getGeometry()->getIndices();
	const Bool need=need_rebuild?True:False;
	if(need!=mNeedRebuild)
	{
		mNeedRebuild=need;
		CSystem::getSingleton().addListener(static_cast<TMessageReceiver<CSystem>*>(this),CSystem::EMessage_BeginUpdate,False);
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CMesh::_rebuild()
{
	if(mNeedRebuild)
	{
		notify(EMessage_BeginRebuild);
		for(UInt32 i=0;i<getInterfaceImp()->getSubMeshCount();++i)
		{
			btIndexedMesh mesh;
			mesh.m_numTriangles=getInterfaceImp()->getSubMesh(i)->getIndexCount()/3;
			mesh.m_numVertices=getInterfaceImp()->getGeometry()->getVertexCount()-getInterfaceImp()->getSubMesh(i)->getVertexStart();
			mesh.m_triangleIndexBase=reinterpret_cast<decltype(mesh.m_triangleIndexBase)>(getInterfaceImp()->getGeometry()->getIndices()+getInterfaceImp()->getSubMesh(i)->getIndexStart());
			mesh.m_triangleIndexStride=3*sizeof(decltype(getInterfaceImp()->getGeometry()->getIndices()[0]));
			mesh.m_vertexBase=reinterpret_cast<decltype(mesh.m_vertexBase)>(getInterfaceImp()->getGeometry()->getPositions()+getInterfaceImp()->getSubMesh(i)->getVertexStart());
			mesh.m_vertexStride=sizeof(decltype(getInterfaceImp()->getGeometry()->getPositions()[0]));
			mesh.m_vertexType=PHY_FLOAT;
			getInternal()->addIndexedMesh(mesh);
		}
		mNeedRebuild=False;
		notify(EMessage_EndRebuild);
	}
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CMesh::SMessageReceiver_IGeometryImp::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryImp::EMessage_EndIndexCountChange:
	case IGeometryImp::EMessage_EndIndicesChange:
	case IGeometryImp::EMessage_EndPositionsChange:
	case IGeometryImp::EMessage_EndVertexCountChange:
		mMesh->_needRebuild();
		break;
	}
}
