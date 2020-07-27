#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ISwapChain
			{
			protected:
				virtual ~ISwapChain(){ }
			public:
				virtual void swapBuffers()=0;
			};
		}
	}
}