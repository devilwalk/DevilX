#pragma once
#include "Player.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CHumanPlayer
			:public CPlayer
			,public TBaseObject<CHumanPlayer>
		{
		protected:
		public:
			CHumanPlayer();
			~CHumanPlayer();
		};
	}
}