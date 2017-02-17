#pragma once
#include "IRenderOverlayElement.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IOverlay
		{
		protected:
			virtual ~IOverlay(){}
		public:
			virtual IOverlayElement * createElement(const String & name)=0;
			virtual IOverlayElement * getElement(const String & name)const=0;
			virtual Void destroyElement(IOverlayElement * element)=0;
		};
	}
}