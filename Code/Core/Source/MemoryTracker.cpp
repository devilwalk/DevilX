#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CMemoryTracker::CMemoryTracker()
{}

NSDevilX::NSCore::CMemoryTracker::~CMemoryTracker()
{
	while(!mRecordChunkList.empty())
	{
		deallocate(mRecordChunkList.begin()->second->mAddress,0,__FILE__,__LINE__,__FUNCTION__);
	}
	for(auto pair_value:mFreeChunkList)
	{
		delete pair_value.first;
		delete pair_value.second;
	}
}

Void NSDevilX::NSCore::CMemoryTracker::allocate(VoidPtr address,size_t size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber)
{
	mRecordChunkListLocker.lockWrite();
	assert(mRecordChunkList.find(address)==mRecordChunkList.end());
	mRecordChunkList[address]=new STrackerChunk(address,size,fileName,functionName,lineNumber,CThreadManager::getCurrentThreadID());
	mRecordChunkListLocker.unLockWrite();
}

Void NSDevilX::NSCore::CMemoryTracker::deallocate(VoidPtr address,UInt32 blockType,ConstCharPtr file,UInt32 line,ConstCharPtr function)
{
	mRecordChunkListLocker.lockWrite();
	STrackerChunk * chunk=nullptr;
	if(mRecordChunkList.find(address)!=mRecordChunkList.end())
	{
		chunk=mRecordChunkList[address];
		mRecordChunkList.erase(address);
	}
	mRecordChunkListLocker.unLockWrite();
	if(chunk)
	{
		if(file)
		{
			mFreeChunkListLocker.lockWrite();
			mFreeChunkList[chunk]=new STrackerChunk(address,chunk->mSize,file,function,line,CThreadManager::getCurrentThreadID());
			mFreeChunkListLocker.unLockWrite();
		}
		else
			delete chunk;
	}
}
