#pragma once
#include "IUIGraphicWindow.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IGraphicScene
		{
		protected:
			virtual ~IGraphicScene(){}
		public:
			virtual NSRenderSystem::IViewport * getRenderViewport()const=0;
			virtual IGraphicWindow * createWindow(const String & name)=0;
			virtual IGraphicWindow * getWindow(const String & name)const=0;
			virtual Void destroyWindow(IGraphicWindow * window)=0;
		};
	}
}