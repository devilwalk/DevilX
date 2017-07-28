#pragma once
#include "UIPageLogic.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CLoginPageLogic
			:public CUIPageLogic
			,public TBaseObject<CLoginPageLogic>
		{
		protected:
		public:
			CLoginPageLogic();
			~CLoginPageLogic();

			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e) override;
		};
	}
}