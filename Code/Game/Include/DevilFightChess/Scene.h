#pragma once
#include "Terrain.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CScene
			:public TBaseObject<CScene>
		{
		protected:
			NSRenderSystem::IScene * mRenderScene;
			CTerrain * mTerrain;
		public:
			CScene();
			~CScene();
			NSRenderSystem::IScene * getRenderScene()const
			{
				return mRenderScene;
			}
		};
	}
}