#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CSystem::CSystem()
	:mSystem(nullptr)
	,mThreadManager(nullptr)
	,mNetworkManager(nullptr)
{
	CMemoryAllocator::sDefault=new CMemoryAllocator;
	DEVILX_NEW CNetworkManager;
	DEVILX_NEW CThreadManager;
	mSystem=new ISystem;
	mThreadManager=new IThreadManager;
	mNetworkManager=new INetworkManager;
	DEVILX_NEW NSGraphicsDriver::ISystemImp;
}

NSDevilX::NSCore::CSystem::~CSystem()
{
	mTimers.destroyAll();
	delete(mNetworkManager);
	delete(mThreadManager);
	delete(mSystem);

	DEVILX_DELETE(CNetworkManager::getSingletonPtr());
	DEVILX_DELETE(CThreadManager::getSingletonPtr());
	DEVILX_DELETE(NSGraphicsDriver::ISystemImp().getSingletonPtr());

	delete CMemoryAllocator::sDefault;
}

ITimerImp * NSDevilX::NSCore::CSystem::createTimer()
{
	auto ret=DEVILX_NEW ITimerImp;
	mTimers.insert(ret);
	return ret;
}

Void NSDevilX::NSCore::CSystem::destroyTimer(ITimerImp * timer)
{
	mTimers.destroy(timer);
}