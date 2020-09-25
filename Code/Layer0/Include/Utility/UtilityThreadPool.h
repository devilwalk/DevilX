#pragma once
namespace NSDevilX
{
	typedef NSCore::IThreadPool::WorkFunction ThreadWorkFunction;
	class CThreadPool
		:public TMemoryAllocatorObject<CThreadPool>
	{
	protected:
		NSCore::IThreadPool * mPool;
		Int32 mNextSyncGroupID;
	public:
		CThreadPool(UInt32 maxThreadCount);
		~CThreadPool();
		Int32 nextSyncGroupID();
		Void submitMT(ThreadWorkFunction func,VoidPtr parameter,Int32 syncGroupID=-1);
		Void doNextWorkMT(Bool wait=False);
		Void waitMT(Int32 syncGroupID);
	};
}