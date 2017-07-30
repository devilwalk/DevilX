#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchServerConfigPageLogic
			:public TBaseObject<CMatchServerConfigPageLogic>
		{
		public:
			static Void buttonLogic(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e);
		};
	}
}