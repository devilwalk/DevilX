#pragma once
namespace NSDevilX
{
	class CReadWriteLocker
	{
	protected:
		NSCore::IReadWriteLock * mInternalLocker;
	public:
		CReadWriteLocker();
		explicit CReadWriteLocker(const CReadWriteLocker & cpy);
		~CReadWriteLocker();
		Void lockRead();
		Void lockWrite();
		Boolean tryLockRead();
		Boolean tryLockWrite();
		Void unLockRead();
		Void unLockWrite();
	};
}