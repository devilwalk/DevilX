#pragma once
#include "HumanPlayer.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CPlayerManager
			:public TBaseObject<CPlayerManager>
		{
		protected:
			TList<CPlayer*> mPlayers;
		public:
			CPlayerManager();
			~CPlayerManager();

			Void initialize(const String & username);
		};
	}
}