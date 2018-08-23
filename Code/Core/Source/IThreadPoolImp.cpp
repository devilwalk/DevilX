#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
namespace NSDevilX
{
	namespace NSCore
	{
		static Void NullWorkFunction(VoidPtr)
		{
		}
	}
}

NSDevilX::NSCore::IThreadPoolImp::IThreadPoolImp()
	:mNextSyncGroupID(0)
{
}

NSDevilX::NSCore::IThreadPoolImp::~IThreadPoolImp()
{
	setMaxThreadCount(0);
	for(auto waiter:mSemaphoreGroups)
	{
		DEVILX_DELETE(waiter.second);
	}
	while(!mFreeWorkerPool.empty())
	{
		CFunctionWorker * worker;
		mFreeWorkerPool.pop(worker);
		DEVILX_DELETE(worker);
	}
}

Void NSDevilX::NSCore::IThreadPoolImp::setMaxThreadCount(UInt32 count)
{
	if(mThreadList.size()<count)
	{
		mThreadList.push_back(DEVILX_NEW SThread(this));
	}
	else if(mThreadList.size()>count)
	{
		for(auto thread:mThreadList)
		{
			thread->mExit=True;
			submit(NullWorkFunction,nullptr);
		}
		for(auto thread:mThreadList)
		{
			DEVILX_DELETE(thread);
		}
		mThreadList.clear();
		setMaxThreadCount(count);
	}
}

UInt32 NSDevilX::NSCore::IThreadPoolImp::getMaxThreadCount() const
{
	return static_cast<UInt32>(mThreadList.size());
}

Void NSDevilX::NSCore::IThreadPoolImp::submit(WorkFunction func,VoidPtr parameter,Int32 syncGroupID)
{
	CFunctionWorker * worker=nullptr;
	if(syncGroupID>=0)
	{
		worker=DEVILX_NEW CFunctionWorker(func,parameter,CThreadManager::getSingleton().getSemaphorePool()->popSemaphore());
		mSemaphoreGroups.lockWrite();
		auto & group_wait=mSemaphoreGroups[syncGroupID];
		if(nullptr==group_wait)
			group_wait=DEVILX_NEW CSemaphoreGroup();
		mSemaphoreGroups.unLockWrite();
		group_wait->addSemaphore(worker->getSemaphore());
	}
	else
	{
		worker=DEVILX_NEW CFunctionWorker(func,parameter);
	}
	mFreeWorkerPool.push(worker);
}

Void NSDevilX::NSCore::IThreadPoolImp::doNextWork(Boolean wait)
{
	CFunctionWorker * worker=nullptr;
	if(wait)
	{
		mFreeWorkerPool.pop(worker);
		(*worker)();
	}
	else
	{
		if(mFreeWorkerPool.try_pop(worker))
		{
			(*worker)();
		}
	}
}

Void NSDevilX::NSCore::IThreadPoolImp::wait(Int32 syncGroupID)
{
	CSemaphoreGroup * group=nullptr;
	mSemaphoreGroups.lockRead();
	if(mSemaphoreGroups.has(syncGroupID))
	{
		group=mSemaphoreGroups.get(syncGroupID);
	}
	mSemaphoreGroups.unLockRead();
	if(group)
	{
		group->wait();
		group->clear(CThreadManager::getSingleton().getSemaphorePool());
	}
}

Void NSDevilX::NSCore::IThreadPoolImp::threadFunction(VoidPtr parameter)
{
	SThread * const thread=static_cast<SThread*>(parameter);
	IThreadPoolImp * const pool=thread->mPool;
	while(!thread->mExit)
	{
		pool->doNextWork(true);
	}
}
