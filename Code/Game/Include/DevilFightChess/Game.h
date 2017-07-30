#pragma once
#include "GameLogic.h"
#include "ServerManager.h"
#include "FontManager.h"
#include "UIManager.h"
#include "Module.h"
#include "MatchServerManager.h"
#include "MatchMapGridRenderMaterialManager.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CGame
			:public TBaseObject<CGame>
		{
		protected:
			NSRenderSystem::IViewport * mViewport;
			CGameLogic * mLogic;
			CServerManager * mServerManager;
			CFontManager * mFontManager;
			CUIManager * mUIManager;
			CMatchServerManager * mMatchServerManager;
			CMatchMapGridRenderMaterialManager * mMatchMapGridRenderMaterialManager;
			NSGUISystem::IScene * mGUIScene;
			TSet<CModule*> mActiveModules;
			TNamedResourcePtrMap<CModule> mModules;
		public:
			CGame();
			~CGame();
			CGameLogic * getLogic()const
			{
				return mLogic;
			}
			CServerManager * getServerManager()const
			{
				return mServerManager;
			}
			CFontManager * getFontManager()const
			{
				return mFontManager;
			}
			CUIManager * getUIManager()const
			{
				return mUIManager;
			}
			CMatchServerManager * getMatchServerManager()const
			{
				return mMatchServerManager;
			}
			CMatchMapGridRenderMaterialManager * getMatchMapGridRenderMaterialManager()const
			{
				return mMatchMapGridRenderMaterialManager;
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
			Void registerModule(CModule * mod);
			Void setModuleParameter(const String & moduleName,const String & name,const CAny & parameter);
			Void startModule(const String & moduleName);
			Void stopModule(const String & moduleName);
			Void update();
			Void messageBox(const CUTF8String & msg);
		};
	}
}