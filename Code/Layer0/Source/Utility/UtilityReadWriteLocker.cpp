#include "Precompiler.h"
using namespace NSDevilX;
NSDevilX::CReadWriteLocker::CReadWriteLocker()
	:mInternalLocker(nullptr)
{
	mInternalLocker=NSCore::getSystem()->getThreadManager()->createReadWriteLock();
}

NSDevilX::CReadWriteLocker::~CReadWriteLocker()
{
	NSCore::getSystem()->getThreadManager()->destroyReadWriteLock(mInternalLocker);
}

Void NSDevilX::CReadWriteLocker::lockRead()
{
	mInternalLocker->lockRead();
}

Void NSDevilX::CReadWriteLocker::lockWrite()
{
	mInternalLocker->lockWrite();
}

Boolean NSDevilX::CReadWriteLocker::tryLockRead()
{
	return mInternalLocker->tryLockRead();
}

Boolean NSDevilX::CReadWriteLocker::tryLockWrite()
{
	return mInternalLocker->tryLockWrite();
}

Void NSDevilX::CReadWriteLocker::unLockRead()
{
	return mInternalLocker->unLockRead();
}

Void NSDevilX::CReadWriteLocker::unLockWrite()
{
	return mInternalLocker->unLockWrite();
}
