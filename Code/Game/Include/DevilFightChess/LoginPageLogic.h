#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CLoginPageLogic
			:public TBaseObject<CLoginPageLogic>
		{
		public:
			static Void buttonLogic(NSGUISystem::IButton * button,NSGUISystem::IButtonEventCallback::EEvent e);
		};
	}
}