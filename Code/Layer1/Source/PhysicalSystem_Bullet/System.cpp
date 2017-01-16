#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
using namespace NSBullet;
ISystem * NSDevilX::NSPhysicalSystem::getSystem()
{
	if(!CSystem::getSingletonPtr())
	{
		DEVILX_NEW ISystemImp;
		DEVILX_NEW CSystem;
	}
	return ISystemImp::getSingletonPtr();
}

Void NSDevilX::NSPhysicalSystem::ISystemImp::update()
{
	CSystem::getSingleton().update();
}

NSDevilX::NSPhysicalSystem::NSBullet::CSystem::CSystem()
	:mResourceManager(0)
{
	mResourceManager=DEVILX_NEW CResourceManager;
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Destruction,False);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_EndSceneCreate,False);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginSceneDestroy,False);
}

NSDevilX::NSPhysicalSystem::NSBullet::CSystem::~CSystem()
{
	DEVILX_DELETE(mResourceManager);
	mInstanceByInterfaceImps.clear();
	mInstanceByInternals.clear();
}

Void NSDevilX::NSPhysicalSystem::NSBullet::CSystem::update()
{
	notify(EMessage_BeginUpdate);
	for(auto p:mScenes)
	{
		CScene * scene=p.second;
		scene->update();
	}
	notify(EMessage_EndUpdate);
}

void NSDevilX::NSPhysicalSystem::NSBullet::CSystem::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_EndSceneCreate:
		mScenes[static_cast<ISceneImp*>(data)]=DEVILX_NEW CScene(static_cast<ISceneImp*>(data));
		break;
	case ISystemImp::EMessage_BeginSceneDestroy:
		mScenes.destroy(static_cast<ISceneImp*>(data));
		break;
	case ISystemImp::EMessage_Destruction:
		DEVILX_DELETE(this);
		break;
	}
}
