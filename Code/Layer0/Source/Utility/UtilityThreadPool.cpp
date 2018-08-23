#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CThreadPool::CThreadPool(UInt32 maxThreadCount)
	:mNextSyncGroupID(0)
	,mPool(nullptr)
{
	mPool=NSCore::getSystem()->getThreadManager()->createThreadPool();
	mPool->setMaxThreadCount(maxThreadCount);
}

NSDevilX::CThreadPool::~CThreadPool()
{
	NSCore::getSystem()->getThreadManager()->destroyThreadPool(mPool);
}

Int32 NSDevilX::CThreadPool::nextSyncGroupID()
{
	return ++mNextSyncGroupID;
}

Void NSDevilX::CThreadPool::submitMT(ThreadWorkFunction func,VoidPtr parameter,Int32 syncGroupID)
{
	mPool->submit(func,parameter,syncGroupID);
}

Void NSDevilX::CThreadPool::doNextWorkMT(Bool wait)
{
	mPool->doNextWork(wait);
}

Void NSDevilX::CThreadPool::waitMT(Int32 syncGroupID)
{
	mPool->wait(syncGroupID);
}