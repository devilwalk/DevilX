#pragma once
namespace NSDevilX
{
	class CMemoryTracer
	{
	public:
		struct STrackerChunk
		{
			const VoidPtr mAddress;
			const SizeT mSize;
			const std::string mFileName;
			const std::string mFunctionName;
			const UInt32 mLineNumber;
			STrackerChunk(VoidPtr address,SizeT size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber)
				:mAddress(address)
				,mSize(size)
				,mFileName(fileName)
				,mFunctionName(functionName)
				,mLineNumber(lineNumber)
			{}
		};
	public:
		static thread_local CMemoryTracer sInstance;
	protected:
		std::map<VoidPtr,STrackerChunk*> mRecordChunkList;
		std::map<STrackerChunk*,STrackerChunk*> mFreeChunkList;
	public:
		Void allocate(VoidPtr address,size_t size,ConstCharPtr fileName,ConstCharPtr functionName,UInt32 lineNumber);
		Void deallocate(VoidPtr address,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr);

	protected:
		CMemoryTracer();
		~CMemoryTracer();
	};
}