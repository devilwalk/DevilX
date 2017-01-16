#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;

NSDevilX::NSPhysicalSystem::IEntityImp::IEntityImp(const String & name,ISceneImp * scene)
	:mName(name)
	,mScene(scene)
	,mMesh(nullptr)
	,mTransformer(nullptr)
	,mOutsideTransformer(False)
{
	mTransformer=DEVILX_NEW ITransformerImp;
}

NSDevilX::NSPhysicalSystem::IEntityImp::~IEntityImp()
{
	if(ISystemImp::getSingleton().isExit())
	{
		if(False==mOutsideTransformer)
			DEVILX_DELETE(mTransformer);
	}
	else
	{
		notify(EMessage_BeginDestruction);
		mSubEntitys.destroyAll();
		if(False==mOutsideTransformer)
			DEVILX_DELETE(mTransformer);
		notify(EMessage_EndDestruction);
	}
}

const String & NSDevilX::NSPhysicalSystem::IEntityImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSPhysicalSystem::IEntityImp::setMesh(IMesh * mesh)
{
	if(mesh!=mMesh)
	{
		notify(EMessage_BeginMeshChange);
		if(mMesh)
		{
			mMesh->removeListener(this,IMeshImp::EMessage_EndSubMeshCreate);
			mMesh->removeListener(this,IMeshImp::EMessage_BeginSubMeshDestroy);
		}
		mMesh=static_cast<IMeshImp*>(mesh);
		_rebuildSubEntitys();
		if(mMesh)
		{
			mMesh->addListener(this,IMeshImp::EMessage_EndSubMeshCreate,False);
			mMesh->addListener(this,IMeshImp::EMessage_BeginSubMeshDestroy,False);
		}
		notify(EMessage_EndMeshChange);
	}
}

IMesh * NSDevilX::NSPhysicalSystem::IEntityImp::getMesh() const
{
	return mMesh;
}

Void NSDevilX::NSPhysicalSystem::IEntityImp::setTransformer(ITransformer * transformer)
{
	if((!transformer)&&(!mOutsideTransformer))
		transformer=mTransformer;
	if(transformer!=mTransformer)
	{
		notify(EMessage_BeginTransformerChange);
		if(transformer)
		{
			DEVILX_DELETE(mTransformer);
			mTransformer=static_cast<ITransformerImp*>(transformer);
			mOutsideTransformer=True;
		}
		else
		{
			mTransformer=DEVILX_NEW ITransformerImp;
			mOutsideTransformer=False;
		}
		notify(EMessage_EndTransformerChange);
	}
}

ITransformer * NSDevilX::NSPhysicalSystem::IEntityImp::getTransformer() const
{
	return mTransformer;
}

ISubEntity * NSDevilX::NSPhysicalSystem::IEntityImp::getSubEntity(ISubMesh * subMesh) const
{
	return mSubEntitys.get(static_cast<ISubMeshImp*>(subMesh));
}

Void NSDevilX::NSPhysicalSystem::IEntityImp::_rebuildSubEntitys()
{
	mSubEntitys.destroyAll();
	if(mMesh)
	{
		for(decltype(mMesh->getSubMeshCount()) i=0;i<mMesh->getSubMeshCount();++i)
		{
			ISubMeshImp * sub_mesh=static_cast<ISubMeshImp*>(mMesh->getSubMesh(i));
			mSubEntitys[sub_mesh]=DEVILX_NEW ISubEntityImp(sub_mesh,this);
		}
	}
}

Void NSDevilX::NSPhysicalSystem::IEntityImp::onMessage(IMeshImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IMeshImp::EMessage_EndSubMeshCreate:
		mSubEntitys[static_cast<ISubMeshImp*>(data)]=DEVILX_NEW ISubEntityImp(static_cast<ISubMeshImp*>(data),this);
		break;
	case IMeshImp::EMessage_BeginSubMeshDestroy:
		mSubEntitys.destroy(static_cast<ISubMeshImp*>(data));
		break;
	}
}
