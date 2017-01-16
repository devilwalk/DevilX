#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
using namespace NSBullet;
NSDevilX::NSPhysicalSystem::NSBullet::CResourceManager::CResourceManager()
{
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(this,IResourceManagerImp::EMessage_EndMeshCreate);
}

NSDevilX::NSPhysicalSystem::NSBullet::CResourceManager::~CResourceManager()
{
}

void NSDevilX::NSPhysicalSystem::NSBullet::CResourceManager::onMessage(IResourceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IResourceManagerImp::EMessage_EndMeshCreate:
		mMeshes[static_cast<IMeshImp*>(data)]=DEVILX_NEW CMesh(static_cast<IMeshImp*>(data));
		break;
	case IResourceManagerImp::EMessage_BeginMeshDestroy:
		mMeshes.destroy(static_cast<IMeshImp*>(data));
		break;
	}
}
