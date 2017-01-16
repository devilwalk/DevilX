#pragma once
#include "CommonDefine.h"
#include "CommonFunctionWorker.h"
#include "CommonSTLMT.h"
#include "CommonReferenceObject.h"
#include "CommonSingleton.h"
#include "CommonThread.h"
namespace NSDevilX
{
	typedef TFunctionWorker<Boolean> CThreadFunctionWorker;
	class CSemaphorePool
		:public TBaseObject<CSemaphorePool>
		,public TSingletonEx<CSemaphorePool>
	{
	protected:
		CPointerQueueMT mFreeWorkerPool;
	public:
		CSemaphorePool();
		~CSemaphorePool();
		CSemaphore * popSemaphoreMT();
		Void pushSemaphoreMT(CSemaphore * semaphore);
	};
	class CThreadPool
		:public TBaseObject<CThreadPool>
	{
	public:
		struct SThread
			:public TBaseObject<SThread>
		{
			CThread * mThread;
			CThreadPool * const mPool;
			SThread(CThreadPool * pool)
				:mPool(pool)
				,mThread(nullptr)
			{
				mThread=DEVILX_NEW CThread(CThreadPool::threadFunction,this);
			}
			~SThread()
			{
				DEVILX_DELETE(mThread);
			}
		};
		typedef TVector<SThread*> ThreadList;
	protected:
		ThreadList mThreadList;
		CPointerQueueMT mFreeWorkerPool;
		TMapMT<Int32,CSemaphoreGroupWait*> mSemaphoreGroupWaits;
		std::atomic<Int32> mNextSyncGroupID;
		volatile Bool mExit;
	public:
		CThreadPool(UInt32 maxThreadCount);
		~CThreadPool();
		Int32 nextSyncGroupID();
		Void submitMT(CThreadFunctionWorker::WorkFunction func,VoidPtr parameter,Int32 syncGroupID=-1);
		Boolean doNextWorkMT(Bool wait=False);
		Void waitMT(Int32 syncGroupID);
		static Void threadFunction(VoidPtr parameter);
	};
	class CDefaultThreadPool
		:public CThreadPool
		,public TSingletonEx<CDefaultThreadPool>
	{
	public:
		CDefaultThreadPool();
		~CDefaultThreadPool();
	};
}