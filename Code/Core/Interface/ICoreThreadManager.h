#pragma once
#include "ICoreReadWriteLock.h"
#include "ICoreSemaphore.h"
#include "ICoreThreadPool.h"
#include "ICoreThread.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI IThreadManager
		{
		public:
			~IThreadManager();
			IReadWriteLock*createReadWriteLock();
			Void destroyReadWriteLock(IReadWriteLock*lock);
			ISemaphore*createSemaphore();
			Void destroySemaphore(ISemaphore*semaphore);
			IThreadPool*createThreadPool();
			Void destroyThreadPool(IThreadPool*pool);
			IThread * createThread();
			Void destroyThread(IThread * thread);
			void sleep(UInt32 timeInMilliseconds);
		};
	}
}