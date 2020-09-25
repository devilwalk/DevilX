#include "Precompiler.h"
using namespace NSDevilX;

thread_local CMemoryTracer CMemoryTracer::sInstance;

NSDevilX::CMemoryTracer::CMemoryTracer()
{}

NSDevilX::CMemoryTracer::~CMemoryTracer()
{
	while(!mRecordChunkList.empty())
	{
		deallocate(mRecordChunkList.begin()->second->mAddress,__FILE__,__LINE__,__FUNCTION__);
	}
	for(auto pair_value:mFreeChunkList)
	{
		delete pair_value.first;
		delete pair_value.second;
	}
}

Void NSDevilX::CMemoryTracer::allocate(VoidPtr address,size_t size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber)
{
	assert(mRecordChunkList.find(address)==mRecordChunkList.end());
	mRecordChunkList[address]=new STrackerChunk(address,size,fileName,functionName,lineNumber);
}

Void NSDevilX::CMemoryTracer::deallocate(VoidPtr address,ConstCharPtr file,UInt32 line,ConstCharPtr function)
{
	STrackerChunk* chunk=nullptr;
	if(mRecordChunkList.find(address)!=mRecordChunkList.end())
	{
		chunk=mRecordChunkList[address];
		mRecordChunkList.erase(address);
	}
	if(chunk)
	{
		if(file)
		{
			mFreeChunkList[chunk]=new STrackerChunk(address,chunk->mSize,file,function,line);
		}
		else
			delete chunk;
	}
}
