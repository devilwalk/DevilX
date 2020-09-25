#pragma once
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
				virtual void swapBuffers()=0;
			};
		}
	}
}