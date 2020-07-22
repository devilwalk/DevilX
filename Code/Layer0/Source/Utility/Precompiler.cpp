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