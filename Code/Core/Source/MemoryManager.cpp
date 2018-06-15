#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

VoidPtr NSDevilX::NSCore::CMemoryManager::allocateBytes(SizeT sizeInBytes)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	return malloc(sizeInBytes);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	return scalable_malloc(sizeInBytes);
#endif
}

Void NSDevilX::NSCore::CMemoryManager::deallocateBytes(VoidPtr address)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	free(address);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	scalable_free(address);
#endif
}

VoidPtr NSDevilX::NSCore::CMemoryManager::alignedAllocateBytes(SizeT sizeInBytes,SizeT alignment)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	return _aligned_malloc(sizeInBytes,alignment);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	return scalable_aligned_malloc(sizeInBytes,alignment);
#endif
}

Void NSDevilX::NSCore::CMemoryManager::alignedDeallocateBytes(VoidPtr address)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	_aligned_free(address);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	scalable_aligned_free(address);
#endif
}
