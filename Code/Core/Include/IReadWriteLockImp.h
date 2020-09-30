#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IReadWriteLockImp
			:public IReadWriteLock
			,public TMemoryAllocatorObject<IReadWriteLockImp>
		{
		protected:
			tbb::queuing_rw_mutex::scoped_lock mLock;
			tbb::queuing_rw_mutex mMutex;
		public:
			IReadWriteLockImp();
			virtual ~IReadWriteLockImp();
			virtual Void lockRead() override;
			virtual Void lockWrite() override;
			virtual Boolean tryLockRead() override;
			virtual Boolean tryLockWrite() override;
			virtual Void unLockRead() override;
			virtual Void unLockWrite() override;
		};
	}
}