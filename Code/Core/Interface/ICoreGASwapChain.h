#pragma once
#include "ICoreGAView.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGASwapChain
		{
		protected:
			virtual ~IGASwapChain(){ }
		public:
			virtual IGARenderTargetView * getRenderTargetView()const=0;
			virtual IGADepthStencilView * getDepthStencilView()const=0;
			virtual Void present()=0;
		};
	}
}