#pragma once
#include "IGDQueue.h"
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
				virtual IQueue* createQueue(IEnum::EQueue type)=0;
			};
		}
	}
}