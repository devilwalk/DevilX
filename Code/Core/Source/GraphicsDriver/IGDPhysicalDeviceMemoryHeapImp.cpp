#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceMemoryHeapImp::IPhysicalDeviceMemoryHeapImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceMemoryHeapImp::~IPhysicalDeviceMemoryHeapImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceMemoryHeapImp::IPhysicalDeviceMemoryHeapImp(UInt32 index,const SMemoryType* types,UInt32 typeCount)
	:mIndex(index)
	,mFlags(0)
	,mTypes(typeCount)
{
	for(UInt32 i=0;i<typeCount;++i)
	{
		mTypes[i]=types[i];
		mFlags|=types[i].mFlags;
	}
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceMemoryHeapImp::~IPhysicalDeviceMemoryHeapImp()
{
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceMemoryHeapImp::getVkMemoryPropertyFlags() const
{
	return mFlags;
}
