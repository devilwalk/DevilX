#pragma once
#include "IGDResource.h"
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
				virtual IImage* createImage(const VkImageCreateInfo& info,const VmaAllocationCreateInfo& allocationInfo)=0;
				virtual IBuffer* createBuffer(const VkImageCreateInfo& info,const VmaAllocationCreateInfo& allocationInfo)=0;
			};
		}
	}
}