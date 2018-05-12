#include "Precompiler.h"
using namespace NSDevilX;

namespace NSDevilX
{
	static Boolean NullWorkFunction(VoidPtr)
	{
		return true;
	}
}

NSDevilX::CSemaphorePool::CSemaphorePool()
{}

NSDevilX::CSemaphorePool::~CSemaphorePool()
{
	CSemaphore * ret=nullptr;
	while(!mFreeWorkerPool.empty())
	{
		ret=mFreeWorkerPool.pop<CSemaphore>();
		DEVILX_DELETE(ret);
	}
}

CSemaphore * NSDevilX::CSemaphorePool::popSemaphoreMT()
{
	CSemaphore * ret=nullptr;
	if(mFreeWorkerPool.empty())
	{
		ret=DEVILX_NEW CSemaphore();
	}
	else
	{
		ret=mFreeWorkerPool.pop<CSemaphore>();
	}
	return ret;
}

Void NSDevilX::CSemaphorePool::pushSemaphoreMT(CSemaphore * semaphore)
{
	mFreeWorkerPool.push(semaphore);
}

NSDevilX::CThreadPool::CThreadPool(UInt32 maxThreadCount,CSemaphorePool * semaphorePool)
	:mSemaphorePool(semaphorePool)
	,mExit(False)
	,mNextSyncGroupID(0)
{
	if(!mSemaphorePool)
		mSemaphorePool=CCommonManager::getSingleton().getSemaphorePool();
	mThreadList.resize(maxThreadCount);
	for(decltype(mThreadList.size()) i=0;i<mThreadList.size();++i)
	{
		mThreadList[i]=DEVILX_NEW SThread(this);
	}
}

NSDevilX::CThreadPool::~CThreadPool()
{
	mExit=True;
	for(auto thread:mThreadList)
	{
		submitMT(NullWorkFunction,nullptr);
	}
	for(auto waiter:mSemaphoreGroupWaits)
	{
		DEVILX_DELETE(waiter.second);
	}
	for(auto thread:mThreadList)
	{
		DEVILX_DELETE(thread);
	}
	while(!mFreeWorkerPool.empty())
	{
		auto worker=mFreeWorkerPool.pop<CThreadFunctionWorker>();
		DEVILX_DELETE(worker);
	}
}

Int32 NSDevilX::CThreadPool::nextSyncGroupID()
{
	return ++mNextSyncGroupID;
}

Void NSDevilX::CThreadPool::submitMT(CThreadFunctionWorker::WorkFunction func,VoidPtr parameter,Int32 syncGroupID)
{
	CThreadFunctionWorker * worker=nullptr;
	if(syncGroupID>=0)
	{
		worker=DEVILX_NEW CThreadFunctionWorker(func,parameter,mSemaphorePool->popSemaphoreMT());
		mSemaphoreGroupWaits.lockWrite();
		CSemaphoreGroupWait * & group_wait=mSemaphoreGroupWaits[syncGroupID];
		if(nullptr==group_wait)
			group_wait=DEVILX_NEW CSemaphoreGroupWait();
		mSemaphoreGroupWaits.unLockWrite();
		group_wait->addSemaphoreMT(worker->getSemaphore());
	}
	else
	{
		worker=DEVILX_NEW CThreadFunctionWorker(func,parameter);
	}
	mFreeWorkerPool.push<CThreadFunctionWorker>(worker);
}

Boolean NSDevilX::CThreadPool::doNextWorkMT(Bool wait)
{
	CThreadFunctionWorker * worker=nullptr;
	if(wait)
	{
		worker=mFreeWorkerPool.pop<CThreadFunctionWorker>();
		if((*worker)())
		{
			DEVILX_DELETE(worker);
		}
		else
		{
			mFreeWorkerPool.push(worker);
		}
		return true;
	}
	else
	{
		mFreeWorkerPool.tryPop(worker);
		if(worker)
		{
			if((*worker)())
			{
				DEVILX_DELETE(worker);
			}
			else
			{
				mFreeWorkerPool.push(worker);
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}

Void NSDevilX::CThreadPool::waitMT(Int32 syncGroupID)
{
	CSemaphoreGroupWait * group=nullptr;
	mSemaphoreGroupWaits.lockRead();
	if(mSemaphoreGroupWaits.has(syncGroupID))
	{
		group=mSemaphoreGroupWaits.get(syncGroupID);
	}
	mSemaphoreGroupWaits.unLockRead();
	if(group)
	{
		group->waitMT();
		group->clearMT(mSemaphorePool);
	}
}

Void NSDevilX::CThreadPool::threadFunction(VoidPtr parameter)
{
	SThread * const thread=static_cast<SThread*>(parameter);
	CThreadPool * const pool=thread->mPool;
	std::mutex locker;
	std::unique_lock<std::mutex> unique_locker(locker);
	while(!pool->mExit)
	{
		pool->doNextWorkMT(True);
	}
}
