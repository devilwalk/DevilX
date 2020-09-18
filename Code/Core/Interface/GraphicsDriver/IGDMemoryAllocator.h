#pragma once
#include "IGDDeviceMemory.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IMemoryAllocator
			{
			protected:
				virtual ~IMemoryAllocator(){}
			public:
				virtual IDeviceMemory* createMemory(D3D12_HEAP_TYPE type,D3D12_HEAP_FLAGS flags,const D3D12_RESOURCE_ALLOCATION_INFO& info)=0;
				virtual IDeviceMemory* createMemory(const VkMemoryRequirements& requirements,VkMemoryPropertyFlags requiredFlags,VkMemoryPropertyFlags preferredFlags)=0;
			};
		}
	}
}