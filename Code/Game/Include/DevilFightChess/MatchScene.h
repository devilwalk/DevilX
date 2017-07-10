#pragma once
#include "MatchTeam.h"
#include "MatchMap.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchScene
			:public TBaseObject<CMatchScene>
		{
		protected:
			NSRenderSystem::IScene * mRenderScene;
			CMatchMap * mMap;
		public:
			CMatchScene();
			~CMatchScene();
			NSRenderSystem::IScene * getRenderScene()const
			{
				return mRenderScene;
			}
			Void loadMap(const CDataStream * dataStream);
		};
	}
}