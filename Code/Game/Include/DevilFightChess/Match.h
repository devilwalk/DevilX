#pragma once
#include "MatchServer.h"
#include "MatchScene.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatch
			:public TBaseObject<CMatch>
		{
		protected:
			CMatchServer * const mServer;
			CMatchScene * mScene;
		public:
			CMatch(CMatchServer * server);
			~CMatch();
		};
	}
}