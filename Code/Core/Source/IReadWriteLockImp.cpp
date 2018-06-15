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
	mLock.lock_read();
}

Void NSDevilX::NSCore::IReadWriteLockImp::lockWrite()
{
	mLock.lock();
}

Boolean NSDevilX::NSCore::IReadWriteLockImp::tryLockRead()
{
	return mLock.try_lock_read();
}

Boolean NSDevilX::NSCore::IReadWriteLockImp::tryLockWrite()
{
	return mLock.try_lock();
}

Void NSDevilX::NSCore::IReadWriteLockImp::unLockRead()
{
	return mLock.unlock();
}

Void NSDevilX::NSCore::IReadWriteLockImp::unLockWrite()
{
	return mLock.unlock();
}
