#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CMemoryManager::CMemoryManager()
#ifdef DEVILX_MEMORY_TRACK_ENABLE
	:mMemoryTracker(nullptr)
#endif
{
#ifdef DEVILX_MEMORY_TRACK_ENABLE
	mMemoryTracker=new CMemoryTracker;
#endif
}

NSDevilX::NSCore::CMemoryManager::~CMemoryManager()
{
#ifdef DEVILX_MEMORY_TRACK_ENABLE
	DEVILX_SAFE_DELETE(mMemoryTracker);
#endif
}

VoidPtr NSDevilX::NSCore::CMemoryManager::allocateBytes(SizeT sizeInBytes,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	VoidPtr ret=nullptr;
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	ret=malloc(sizeInBytes);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	ret=scalable_malloc(sizeInBytes);
#endif
#ifdef DEVILX_MEMORY_TRACK_ENABLE
	if(file)
		mMemoryTracker->allocate(ret,sizeInBytes,file,function,line);
#endif
	return ret;
}

Void NSDevilX::NSCore::CMemoryManager::deallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	free(address);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	scalable_free(address);
#endif
#ifdef DEVILX_MEMORY_TRACK_ENABLE
	mMemoryTracker->deallocate(address,file,function,line);
#endif
}

VoidPtr NSDevilX::NSCore::CMemoryManager::alignedAllocateBytes(SizeT sizeInBytes,SizeT alignment,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	VoidPtr ret=nullptr;
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	ret=_aligned_malloc(sizeInBytes,alignment);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	ret=scalable_aligned_malloc(sizeInBytes,alignment);
#endif
#ifdef DEVILX_MEMORY_TRACK_ENABLE
	if(file)
		mMemoryTracker->allocate(ret,sizeInBytes,file,function,line);
#endif
	return ret;
}

Void NSDevilX::NSCore::CMemoryManager::alignedDeallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	_aligned_free(address);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	scalable_aligned_free(address);
#endif
#ifdef DEVILX_MEMORY_TRACK_ENABLE
	mMemoryTracker->deallocate(address,file,function,line);
#endif
}
