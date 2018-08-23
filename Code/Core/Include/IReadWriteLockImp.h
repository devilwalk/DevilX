#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IReadWriteLockImp
			:public IReadWriteLock
			,public TBaseObject<IReadWriteLockImp>
		{
		protected:
			tbb::interface5::reader_writer_lock mLock;
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