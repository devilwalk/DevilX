#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CCreateRoom
			:public TBaseObject<CCreateRoom>
			,public CModule
		{
		protected:
		public:
			CCreateRoom();
			~CCreateRoom();
		};
	}
}