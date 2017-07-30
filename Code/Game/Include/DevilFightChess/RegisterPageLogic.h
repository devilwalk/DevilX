#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CRegisterPageLogic
			:public TBaseObject<CRegisterPageLogic>
		{
		public:
			static Void buttonLogic(NSGUISystem::IButton * button,NSGUISystem::IButtonEventCallback::EEvent e);
		};
	}
}