#pragma once
#define DEVILX_ALLOCATOR_STANDER 0
#define DEVILX_ALLOCATOR_TBB 1
#define DEVILX_ALLOCATOR DEVILX_ALLOCATOR_TBB
namespace NSDevilX
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
#define TAllocator std::allocator
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
#define TAllocator tbb::tbb_allocator
#endif
}