#include "Precompiler.h"
using namespace NSDevilX;
VoidPtr NSDevilX::allocateBytes(SizeT sizeInBytes)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	return malloc(sizeInBytes);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	return scalable_malloc(sizeInBytes);
#endif
}
Void NSDevilX::deallocateBytes(VoidPtr address)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	free(address);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	scalable_free(address);
#endif
}
VoidPtr NSDevilX::alignedAllocateBytes(SizeT sizeInBytes,SizeT alignment)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	return _aligned_malloc(sizeInBytes,alignment);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	return scalable_aligned_malloc(sizeInBytes,alignment);
#endif
}
Void NSDevilX::alignedDeallocateBytes(VoidPtr address)
{
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
	_aligned_free(address);
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
	scalable_aligned_free(address);
#endif
}
VoidPtr NSDevilX::trackAllocateBytes(SizeT sizeInBytes,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	VoidPtr ret=allocateBytes(sizeInBytes);
	getDefaultMemoryTracker()->allocate(ret,sizeInBytes,file,function,line);
	return ret;
}
Void NSDevilX::trackDeallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	getDefaultMemoryTracker()->deallocate(address,file,function,line);
	deallocateBytes(address);
}
VoidPtr NSDevilX::trackAlignedAllocateBytes(SizeT sizeInBytes,SizeT alignment,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	VoidPtr ret=alignedAllocateBytes(sizeInBytes,alignment);
	getDefaultMemoryTracker()->allocate(ret,sizeInBytes,file,function,line);
	return ret;
}
Void NSDevilX::trackAlignedDeallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	getDefaultMemoryTracker()->deallocate(address,file,function,line);
	alignedDeallocateBytes(address);
}
const UInt32 NSDevilX::CQuadTreeNode::sChildrenIndex[]={0,1,3,2};
const UInt32 NSDevilX::COctreeNode::sChildrenIndex[]={4,5,7,6,0,1,3,2};
const String NSDevilX::CStringConverter::sBlank("");