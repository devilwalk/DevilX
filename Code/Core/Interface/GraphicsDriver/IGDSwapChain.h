#pragma once
#include "IGDResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ICommandQueue;
			class ISwapChain
			{
			protected:
				virtual ~ISwapChain(){ }
			public:
				virtual ICommandQueue* getCommandQueue()const=0;
				virtual UInt32 getBackBufferCount()const=0;
				virtual IImage* getBackBuffer(UInt32 index)const=0;
				virtual void swapBuffers()=0;
			};
		}
	}
}