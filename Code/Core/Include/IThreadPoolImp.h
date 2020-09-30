#pragma once
#include "FunctionWorker.h"
#include "SemaphoreGroup.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IThreadPoolImp
			:public IThreadPool
			,public TMemoryAllocatorObject<IThreadPoolImp>
		{
		public:
			struct SThread
				:public TMemoryAllocatorObject<SThread>
			{
				std::thread * mThread;
				IThreadPoolImp * const mPool;
				std::atomic<Bool> mExit;
				SThread(IThreadPoolImp * pool)
					:mThread(nullptr)
					,mPool(pool)
					,mExit(False)
				{
					mThread=new std::thread(IThreadPoolImp::threadFunction,this);
				}
				~SThread()
				{
					mThread->join();
					delete mThread;
				}
			};
		protected:
			tbb::concurrent_vector<SThread*> mThreadList;
			tbb::concurrent_bounded_queue<CFunctionWorker*> mFreeWorkerPool;
			TMapMT<Int32,CSemaphoreGroup*> mSemaphoreGroups;
			Int32 mNextSyncGroupID;
		public:
			IThreadPoolImp();
			~IThreadPoolImp();

			// Í¨¹ý IThreadPool ¼Ì³Ð
			virtual Void setMaxThreadCount(UInt32 count) override;
			virtual UInt32 getMaxThreadCount() const override;
			virtual Void submit(WorkFunction func,VoidPtr parameter,Int32 syncGroupID=-1) override;
			virtual Void doNextWork(Boolean wait=false) override;
			virtual Void wait(Int32 syncGroupID) override;
			static Void threadFunction(VoidPtr parameter);
		};
	}
}