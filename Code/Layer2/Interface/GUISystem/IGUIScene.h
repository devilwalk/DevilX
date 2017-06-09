#pragma once
#include "IGUIWindow.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IScene
		{
		protected:
			virtual ~IScene(){}
		public:
			virtual NSRenderSystem::IViewport * getRenderViewport()const=0;
			virtual IWindow * createWindow(const String & name,Bool isModule=False)=0;
			virtual IWindow * getWindow(const String & name)const=0;
			virtual Void destroyWindow(IWindow * window)=0;
		};
	}
}