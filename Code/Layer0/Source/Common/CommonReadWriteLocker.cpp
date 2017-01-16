#include "Precompiler.h"
using namespace NSDevilX;
NSDevilX::CReadWriteLocker::CReadWriteLocker()
	:mInternalLocker(0)
{
	mInternalLocker=new tbb::interface5::reader_writer_lock();
}

NSDevilX::CReadWriteLocker::~CReadWriteLocker()
{
	delete static_cast<tbb::interface5::reader_writer_lock*>(mInternalLocker);
}

Void NSDevilX::CReadWriteLocker::lockRead()
{
	static_cast<tbb::interface5::reader_writer_lock*>(mInternalLocker)->lock_read();
}

Void NSDevilX::CReadWriteLocker::lockWrite()
{
	static_cast<tbb::interface5::reader_writer_lock*>(mInternalLocker)->lock();
}

Boolean NSDevilX::CReadWriteLocker::tryLockRead()
{
	return static_cast<tbb::interface5::reader_writer_lock*>(mInternalLocker)->try_lock_read();
}

Boolean NSDevilX::CReadWriteLocker::tryLockWrite()
{
	return static_cast<tbb::interface5::reader_writer_lock*>(mInternalLocker)->try_lock();
}

Void NSDevilX::CReadWriteLocker::unLockRead()
{
	return static_cast<tbb::interface5::reader_writer_lock*>(mInternalLocker)->unlock();
}

Void NSDevilX::CReadWriteLocker::unLockWrite()
{
	return static_cast<tbb::interface5::reader_writer_lock*>(mInternalLocker)->unlock();
}
