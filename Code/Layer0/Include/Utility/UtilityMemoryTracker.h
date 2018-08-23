#pragma once
#include "UtilityThreadType.h"
#include "UtilityThreadManager.h"
#include "UtilityReadWriteLocker.h"
namespace NSDevilX
{
	class CMemoryTracker
	{
	public:
		struct STrackerChunk
		{
			const VoidPtr mAddress;
			const SizeT mSize;
			const std::string mFileName;
			const std::string mFunctionName;
			const UInt32 mLineNumber;
			const SizeT mThreadID;
			STrackerChunk(VoidPtr address,SizeT size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber,SizeT threadID)
				:mAddress(address)
				,mSize(size)
				,mFileName(fileName)
				,mFunctionName(functionName)
				,mLineNumber(lineNumber)
				,mThreadID(threadID)
			{}
		};
	protected:
		const ThreadID mThreadID;
		std::map<VoidPtr,STrackerChunk*> mRecordChunkList;
		std::map<STrackerChunk*,STrackerChunk*> mFreeChunkList;
	public:
		CMemoryTracker(ThreadID threadID)
			:mThreadID(threadID)
		{}
		virtual ~CMemoryTracker()
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
		ThreadID getThreadID()const
		{
			return mThreadID;
		}
		virtual Void allocate(VoidPtr address,size_t size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber)
		{
			assert(CThreadManager::getCurrentThreadID()==mThreadID);
			assert(mRecordChunkList.find(address)==mRecordChunkList.end());
			mRecordChunkList[address]=new STrackerChunk(address,size,fileName,functionName,lineNumber,getThreadID());
		}
		virtual Void deallocate(VoidPtr address,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber)
		{
			assert(CThreadManager::getCurrentThreadID()==mThreadID);
			assert(mRecordChunkList.find(address)!=mRecordChunkList.end());
			STrackerChunk * chunk=mRecordChunkList[address];
			mRecordChunkList.erase(address);
			assert(mFreeChunkList.find(chunk)==mFreeChunkList.end());
			mFreeChunkList[chunk]=new STrackerChunk(address,chunk->mSize,fileName,functionName,lineNumber,getThreadID());
		}
	};
	class CDefaultMemoryTracker
		:public CMemoryTracker
	{
	protected:
		CReadWriteLocker mRecordChunkListLocker;
		CReadWriteLocker mFreeChunkListLocker;
	public:
		CDefaultMemoryTracker()
			:CMemoryTracker(0)
		{}
		~CDefaultMemoryTracker()
		{
		}
		virtual Void allocate(VoidPtr address,size_t size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber) override
		{
			mRecordChunkListLocker.lockRead();
			assert(mRecordChunkList.find(address)==mRecordChunkList.end());
			mRecordChunkListLocker.unLockRead();
			mRecordChunkListLocker.lockWrite();
			mRecordChunkList[address]=new STrackerChunk(address,size,fileName,functionName,lineNumber,CThreadManager::getCurrentThreadID());
			mRecordChunkListLocker.unLockWrite();
		}
		virtual Void deallocate(VoidPtr address,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber) override
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
			mFreeChunkList[chunk]=new STrackerChunk(address,chunk->mSize,fileName,functionName,lineNumber,CThreadManager::getCurrentThreadID());
			mFreeChunkListLocker.unLockWrite();
		}
	};
	CMemoryTracker * getMemoryTracker();
	CDefaultMemoryTracker * getDefaultMemoryTracker();
	Void destroyMemoryTracker();
}