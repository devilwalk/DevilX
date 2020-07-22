#pragma once
#include "FunctionWorker.h"
#include "SemaphoreGroup.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IThreadPoolImp
			:public IThreadPool
			,public TBaseObject<IThreadPoolImp>
		{
		public:
			struct SThread
				:public TBaseObject<SThread>
			{
				std::thread * mThread;
				IThreadPoolImp * const mPool;
				std::atomic<Bool> mExit;
				SThread(IThreadPoolImp * pool)
					:mThread(nullptr)
					,mPool(pool)
					,mExit(False)
				{
					mThread=DEVILX_TYPED_ALLOC(std::thread,1);
					mThread->std::thread::thread(IThreadPoolImp::threadFunction,this);
				}
				~SThread()
				{
					mThread->join();
					DEVILX_OBJECT_DELETE(mThread);
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