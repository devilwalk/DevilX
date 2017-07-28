#pragma once
#include "UIPageLogic.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CBigWorldPageLogic
			:public CUIPageLogic
			,public TBaseObject<CBigWorldPageLogic>
		{
		protected:
		public:
			CBigWorldPageLogic();
			~CBigWorldPageLogic();

			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e) override;
		};
	}
}