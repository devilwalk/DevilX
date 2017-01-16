#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CSemaphore::CSemaphore()
	:mInternal(nullptr)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	mInternal=CreateEvent(nullptr,FALSE,FALSE,nullptr);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

NSDevilX::CSemaphore::~CSemaphore()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	CloseHandle(mInternal);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

Void NSDevilX::CSemaphore::notify()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	SetEvent(mInternal);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

Void NSDevilX::CSemaphore::wait()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	WaitForSingleObject(mInternal,INFINITE);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

NSDevilX::CSemaphoreGroupWait::CSemaphoreGroupWait()
{}

NSDevilX::CSemaphoreGroupWait::~CSemaphoreGroupWait()
{}

Void NSDevilX::CSemaphoreGroupWait::addSemaphoreMT(CSemaphore * semaphore)
{
	mSemaphores.pushBackMT(semaphore);
}

Void NSDevilX::CSemaphoreGroupWait::waitMT()
{
	mSemaphores.lockRead();
	for(auto semaphore:mSemaphores)
	{
		semaphore->wait();
	}
	mSemaphores.unLockRead();
}

Void NSDevilX::CSemaphoreGroupWait::clearMT(CSemaphorePool * pool)
{
	mSemaphores.lockWrite();
	if(pool)
	{
		for(auto semaphore:mSemaphores)
			pool->pushSemaphoreMT(semaphore);
	}
	mSemaphores.clear();
	mSemaphores.unLockWrite();
}
