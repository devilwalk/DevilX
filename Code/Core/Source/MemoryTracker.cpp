#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CMemoryTracker::CMemoryTracker()
{}

NSDevilX::NSCore::CMemoryTracker::~CMemoryTracker()
{
	while(!mRecordChunkList.empty())
	{
		deallocate(mRecordChunkList.begin()->second->mAddress,__FILE__,__FUNCTION__,__LINE__);
	}
	for(auto pair_value:mFreeChunkList)
	{
		delete pair_value.first;
		delete pair_value.second;
	}
}

Void NSDevilX::NSCore::CMemoryTracker::allocate(VoidPtr address,size_t size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber)
{
	mRecordChunkListLocker.lockRead();
	assert(mRecordChunkList.find(address)==mRecordChunkList.end());
	mRecordChunkListLocker.unLockRead();
	mRecordChunkListLocker.lockWrite();
	mRecordChunkList[address]=new STrackerChunk(address,size,fileName,functionName,lineNumber,CThreadManager::getSingleton().getCurrentThreadID());
	mRecordChunkListLocker.unLockWrite();
}

Void NSDevilX::NSCore::CMemoryTracker::deallocate(VoidPtr address,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber)
{
	mRecordChunkListLocker.lockRead();
	assert(mRecordChunkList.find(address)!=mRecordChunkList.end());
	STrackerChunk * chunk=mRecordChunkList[address];
	mRecordChunkListLocker.unLockRead();
	mRecordChunkListLocker.lockWrite();
	mRecordChunkList.erase(address);
	mRecordChunkListLocker.unLockWrite();
	mFreeChunkListLocker.lockRead();
	assert(mFreeChunkList.find(chunk)==mFreeChunkList.end());
	mFreeChunkListLocker.unLockRead();
	mFreeChunkListLocker.lockWrite();
	mFreeChunkList[chunk]=new STrackerChunk(address,chunk->mSize,fileName,functionName,lineNumber,CThreadManager::getSingleton().getCurrentThreadID());
	mFreeChunkListLocker.unLockWrite();
}
