#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CBigWorldPageLogic
			:public TBaseObject<CBigWorldPageLogic>
		{
		public:
			static Void buttonLogic(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e);
		};
	}
}