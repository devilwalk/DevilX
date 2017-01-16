#pragma once
#include "IRenderViewport.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderTarget
		{
		protected:
			virtual ~IRenderTarget(){}
		public:
			virtual UInt32 getWidth()const=0;
			virtual UInt32 getHeight()const=0;
			virtual IViewport * createViewport(const String & name)=0;
			virtual Void destroyViewport(IViewport * viewport)=0;
			virtual IViewport * getViewport(const String & name)const=0;
			virtual Void setClearColour(const CColour & colour)=0;
			virtual const CColour & getClearColour()const=0;
		};
		class IWindow
		{
		protected:
			virtual ~IWindow(){}
		public:
			virtual IRenderTarget * queryInterface_IRenderTarget()const=0;
			virtual Void resize()=0;
		};
	}
}