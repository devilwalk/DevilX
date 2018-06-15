#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CSemaphorePool::CSemaphorePool()
{}

NSDevilX::NSCore::CSemaphorePool::~CSemaphorePool()
{
	ISemaphoreImp * ret=nullptr;
	while(!mFreeWorkerPool.empty())
	{
		mFreeWorkerPool.pop(ret);
		delete ret;
	}
}

ISemaphoreImp * NSDevilX::NSCore::CSemaphorePool::popSemaphore()
{
	ISemaphoreImp * ret=nullptr;
	if(mFreeWorkerPool.empty())
	{
		ret=new ISemaphoreImp();
	}
	else
	{
		mFreeWorkerPool.pop(ret);
	}
	return ret;
}

Void NSDevilX::NSCore::CSemaphorePool::pushSemaphore(ISemaphoreImp * semaphore)
{
	mFreeWorkerPool.push(semaphore);
}

NSDevilX::NSCore::CSemaphoreGroup::CSemaphoreGroup()
{}

NSDevilX::NSCore::CSemaphoreGroup::~CSemaphoreGroup()
{}

Void NSDevilX::NSCore::CSemaphoreGroup::addSemaphore(ISemaphoreImp * semaphore)
{
	mSemaphores.pushBackMT(semaphore);
}

Void NSDevilX::NSCore::CSemaphoreGroup::wait()
{
	mSemaphores.lockRead();
	for(auto semaphore:mSemaphores)
	{
		semaphore->wait(-1);
	}
	mSemaphores.unLockRead();
}

Void NSDevilX::NSCore::CSemaphoreGroup::clear(CSemaphorePool * pool)
{
	mSemaphores.lockWrite();
	if(pool)
	{
		for(auto semaphore:mSemaphores)
			pool->pushSemaphore(semaphore);
	}
	mSemaphores.clear();
	mSemaphores.unLockWrite();
}
