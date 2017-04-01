#pragma once
#include "Game.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CApp
			:public TBaseObject<CApp>
			,public TSingletonEx<CApp>
		{
		protected:
			CWindow * mWindow;
			NSRenderSystem::IWindow * mRenderWindow;
			CGame * mGame;
		public:
			CApp();
			~CApp();
			CWindow * getWindow()const
			{
				return mWindow;
			}
			CGame * getGame()const
			{
				return mGame;
			}
			NSRenderSystem::IWindow * getRenderWindow()const
			{
				return mRenderWindow;
			}
			Void run();
		};
	}
}