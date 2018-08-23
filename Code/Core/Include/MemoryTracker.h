#pragma once
#include "IReadWriteLockImp.h"
namespace NSDevilX
{
	namespace NSCore
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
			TMap<VoidPtr,STrackerChunk*> mRecordChunkList;
			TMap<STrackerChunk*,STrackerChunk*> mFreeChunkList;
			IReadWriteLockImp mRecordChunkListLocker;
			IReadWriteLockImp mFreeChunkListLocker;
		public:
			CMemoryTracker();
			~CMemoryTracker();
			Void allocate(VoidPtr address,size_t size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber);
			Void deallocate(VoidPtr address,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber);
		};
	}
}