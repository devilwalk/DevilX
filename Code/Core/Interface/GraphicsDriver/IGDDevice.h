#pragma once
#include "IGDCommandQueue.h"
#include "IGDCommandAllocator.h"
#include "IGDMemoryAllocator.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IDevice
			{
			protected:
				virtual ~IDevice()
				{
				}
			public:
				virtual ICommandQueue* createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice=nullptr)=0;
				virtual ICommandAllocator* createCommandAllocator(IEnum::ECommandQueue type)=0;
				virtual IMemoryAllocator* getDefaultMemoryAllocator()const=0;
			};
		}
	}
}