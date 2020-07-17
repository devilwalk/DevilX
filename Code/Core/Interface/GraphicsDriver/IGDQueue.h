#pragma once
#include "IGDSwapChain.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IQueue
			{
			protected:
				virtual ~IQueue(){ }
			public:
				virtual ISwapChain* createSwapChain()=0;
			};
		}
	}
}