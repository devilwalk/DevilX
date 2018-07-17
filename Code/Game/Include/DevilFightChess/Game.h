#pragma once
#include "GameLogic.h"
#include "ServerManager.h"
#include "FontManager.h"
#include "UIManager.h"
#include "Module.h"
#include "MatchServerManager.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CGame
			:public TBaseObject<CGame>
		{
		public:
			struct SModule
			{
				CModule * mModule;
				Bool mActived;
				SModule(CModule * mod=nullptr)
					:mModule(mod)
					,mActived(False)
				{}
				~SModule()
				{
					if(mModule)
						DEVILX_DELETE(mModule);
				}
			};
		protected:
			NSRenderSystem::IViewport * mViewport;
			CGameLogic * mLogic;
			CServerManager * mServerManager;
			CFontManager * mFontManager;
			CUIManager * mUIManager;
			CMatchServerManager * mMatchServerManager;
			NSGUISystem::IScene * mGUIScene;
			TNamedResourcePtrMap<SModule> mModules;
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