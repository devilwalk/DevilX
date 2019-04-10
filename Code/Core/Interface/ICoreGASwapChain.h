#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGASwapChain
		{
		protected:
			virtual ~IGASwapChain(){ }
		public:
			virtual Void present()=0;
		};
	}
}