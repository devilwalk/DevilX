#pragma once
#include "IUIEnum.h"
#include "IUIEventScene.h"
#include "IUIGraphicScene.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual IEventScene * createEventScene(const String & name)=0;
			virtual IEventScene * getEventScene(const String & name)const=0;
			virtual Void destroyEventScene(IEventScene * window)=0;
			virtual IGraphicScene * createGraphicScene(NSRenderSystem::IViewport * viewport)=0;
			virtual IGraphicScene * getGraphicScene(NSRenderSystem::IViewport * viewport)const=0;
			virtual Void destroyGraphicScene(IGraphicScene * window)=0;
		};
		ISystem * getSystem();
	}
}