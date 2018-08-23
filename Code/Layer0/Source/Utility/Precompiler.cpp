#include "Precompiler.h"
using namespace NSDevilX;
VoidPtr NSDevilX::trackAllocateBytes(SizeT sizeInBytes,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	VoidPtr ret=DEVILX_ALLOC(sizeInBytes);
	getDefaultMemoryTracker()->allocate(ret,sizeInBytes,file,function,line);
	return ret;
}
Void NSDevilX::trackDeallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	getDefaultMemoryTracker()->deallocate(address,file,function,line);
	DEVILX_FREE(address);
}
VoidPtr NSDevilX::trackAlignedAllocateBytes(SizeT sizeInBytes,SizeT alignment,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	VoidPtr ret=DEVILX_ALIGNED_ALLOC(sizeInBytes,alignment);
	getDefaultMemoryTracker()->allocate(ret,sizeInBytes,file,function,line);
	return ret;
}
Void NSDevilX::trackAlignedDeallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
{
	getDefaultMemoryTracker()->deallocate(address,file,function,line);
	DEVILX_ALIGNED_FREE(address);
}
const UInt32 NSDevilX::CQuadTreeNode::sChildrenIndex[]={0,1,3,2};
const UInt32 NSDevilX::COctreeNode::sChildrenIndex[]={4,5,7,6,0,1,3,2};