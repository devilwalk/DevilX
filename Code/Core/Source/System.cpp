#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CSystem::CSystem()
	:mSystem(nullptr)
	,mMemoryManager(nullptr)
	,mThreadManager(nullptr)
	,mNetworkManager(nullptr)
	,mGAManager(nullptr)
{
	DEVILX_NEW NSDirectX::CGAManager;
	DEVILX_NEW NSOpenGL::CGAManager;
	DEVILX_NEW CNetworkManager;
	DEVILX_NEW CThreadManager;
	mSystem=DEVILX_TYPED_ALLOC(ISystem,1);
	mMemoryManager=DEVILX_TYPED_ALLOC(IMemoryManager,1);
	mThreadManager=DEVILX_TYPED_ALLOC(IThreadManager,1);
	mNetworkManager=DEVILX_TYPED_ALLOC(INetworkManager,1);
	mGAManager=DEVILX_TYPED_ALLOC(IGAManager,1);
}

NSDevilX::NSCore::CSystem::~CSystem()
{
	mTimers.destroyAll();
	DEVILX_FREE(mGAManager);
	DEVILX_FREE(mNetworkManager);
	DEVILX_FREE(mThreadManager);
	DEVILX_FREE(mMemoryManager);
	DEVILX_FREE(mSystem);

	DEVILX_DELETE(NSDirectX::CGAManager::getSingletonPtr());
	DEVILX_DELETE(NSOpenGL::CGAManager::getSingletonPtr());
	DEVILX_DELETE(CNetworkManager::getSingletonPtr());
	DEVILX_DELETE(CThreadManager::getSingletonPtr());
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