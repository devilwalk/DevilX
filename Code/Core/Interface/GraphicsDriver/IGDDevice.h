#pragma once
#include "IGDQueue.h"
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
				virtual UInt32 getQueueCount(IEnum::EQueue type)const=0;
				virtual IQueue* getQueue(IEnum::EQueue type,UInt32 index)=0;
				virtual IMemoryAllocator* createMemoryAllocator(UInt32 flags,UInt32 preferredBlockSize=0)=0;
			};
		}
	}
}