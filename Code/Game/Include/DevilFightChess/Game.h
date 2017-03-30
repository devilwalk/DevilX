#pragma once
#include "ServerManager.h"
#include "FontManager.h"
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CGame
			:public TBaseObject<CGame>
		{
		protected:
			NSRenderSystem::IViewport * mViewport;
			CServerManager * mServerManager;
			CFontManager * mFontManager;
			NSGUISystem::IScene * mGUIScene;
			TSet<CModule*> mActiveModules;
			TNamedResourcePtrMap<CModule> mModules;
		public:
			CGame();
			~CGame();
			CServerManager * getServerManager()const
			{
				return mServerManager;
			}
			CFontManager * getFontManager()const
			{
				return mFontManager;
			}
			NSGUISystem::IScene * getGUIScene()const
			{
				return mGUIScene;
			}
			NSRenderSystem::IViewport * getViewport()const
			{
				return mViewport;
			}
			Void initialize();
			Void registerModule(CModule * module);
			Void startModule(const String & moduleName);
			Void stopModule(const String & moduleName);
			Void update();
		};
	}
}