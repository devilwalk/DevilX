#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CThreadManager::CThreadManager()
	:mSemaphorePool(nullptr)
{
	mSemaphorePool=DEVILX_NEW CSemaphorePool;
}

NSDevilX::NSCore::CThreadManager::~CThreadManager()
{
	DEVILX_DELETE(mSemaphorePool);
}

ThreadID NSDevilX::NSCore::CThreadManager::getCurrentThreadID()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	return ::GetCurrentThreadId();
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	return pthread_self();
#endif
}

Void NSDevilX::NSCore::CThreadManager::sleep(UInt32 timeInMilliseconds)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	Sleep(timeInMilliseconds);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	usleep(timeInMilliseconds);
#endif
}
