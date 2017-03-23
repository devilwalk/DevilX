#pragma once
#include "IRenderTarget.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IWindow
		{
		protected:
			virtual ~IWindow(){}
		public:
			virtual IRenderTarget * queryInterface_IRenderTarget()const=0;
			virtual CWindow * getWindow()const=0;
		};
	}
}