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
			virtual IViewport * createViewport(const String & name)=0;
			virtual Void destroyViewport(IViewport * viewport)=0;
			virtual IViewport * getViewport(const String & name)const=0;
			virtual Void setClearColour(const CColour & colour)=0;
			virtual const CColour & getClearColour()const=0;
		};
	}
}