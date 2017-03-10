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
			virtual Void setFontManager(CFontManager * manager)=0;
			virtual CFontManager * getFontManager()const=0;
			virtual Void setFontName(const String & fontName)=0;
			virtual const String & getFontName()const=0;
			virtual IScene * createScene(NSRenderSystem::IViewport * viewport)=0;
			virtual IScene * getScene(NSRenderSystem::IViewport * viewport)const=0;
			virtual Void destroyScene(IScene * scene)=0;
			virtual Void shutdown()=0;
		};
		ISystem * getSystem();
	}
}