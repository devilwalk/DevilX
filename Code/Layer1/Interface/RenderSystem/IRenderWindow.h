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
			virtual UInt32 getWidth()const=0;
			virtual UInt32 getHeight()const=0;
			virtual Void resize()=0;
		};
	}
}