#pragma once
#include "UIPageLogic.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CRegisterPageLogic
			:public CUIPageLogic
			,public TBaseObject<CRegisterPageLogic>
		{
		protected:
		public:
			CRegisterPageLogic();
			~CRegisterPageLogic();

			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e) override;
		};
	}
}