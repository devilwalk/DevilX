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
		protected:
			~IThreadManager();
		public:
			IReadWriteLock*createReadWriteLock();
			void destroyReadWriteLock(IReadWriteLock*lock);
			ISemaphore*createSemaphore();
			void destroySemaphore(ISemaphore*semaphore);
			IThreadPool*createThreadPool();
			void destroyThreadPool(IThreadPool*pool);
			IThread * createThread();
			void destroyThread(IThread * thread);
			void sleep(unsigned int timeInMilliseconds);
		};
	}
}