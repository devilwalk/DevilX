#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CSemaphorePool
			:public TMemoryAllocatorObject<CSemaphorePool>
		{
		protected:
			tbb::concurrent_bounded_queue<ISemaphoreImp*> mFreeWorkerPool;
		public:
			CSemaphorePool();
			~CSemaphorePool();
			ISemaphoreImp * popSemaphore();
			Void pushSemaphore(ISemaphoreImp * semaphore);
		};
		class CSemaphoreGroup
			:public TMemoryAllocatorObject<CSemaphoreGroup>
		{
		protected:
			TVectorMT<ISemaphoreImp*> mSemaphores;
		public:
			CSemaphoreGroup();
			~CSemaphoreGroup();
			Void addSemaphore(ISemaphoreImp * semaphore);
			Void wait();
			Void clear(CSemaphorePool * pool=nullptr);
		};
	}
}