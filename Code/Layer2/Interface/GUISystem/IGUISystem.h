#pragma once
#include "IGUIScene.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual IScene * createScene(NSRenderSystem::IViewport * viewport)=0;
			virtual IScene * getScene(NSRenderSystem::IViewport * viewport)const=0;
			virtual Void destroyScene(IScene * scene)=0;
			virtual Void update()=0;
			virtual Void shutdown()=0;
		};
		ISystem * getSystem();
	}
}