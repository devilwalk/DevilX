#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IReadWriteLockImp::IReadWriteLockImp()
{
}

NSDevilX::NSCore::IReadWriteLockImp::~IReadWriteLockImp()
{
}

Void NSDevilX::NSCore::IReadWriteLockImp::lockRead()
{
	mLock.acquire(mMutex,false);
}

Void NSDevilX::NSCore::IReadWriteLockImp::lockWrite()
{
	mLock.acquire(mMutex);
}

Boolean NSDevilX::NSCore::IReadWriteLockImp::tryLockRead()
{
	return mLock.try_acquire(mMutex,false);
}

Boolean NSDevilX::NSCore::IReadWriteLockImp::tryLockWrite()
{
	return mLock.try_acquire(mMutex);
}

Void NSDevilX::NSCore::IReadWriteLockImp::unLockRead()
{
	return mLock.release();
}

Void NSDevilX::NSCore::IReadWriteLockImp::unLockWrite()
{
	return mLock.release();
}
