#pragma once
#include "UIPage.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIPageLogic
			:public NSGUISystem::IButtonEventCallback
			,public NSGUISystem::IEditBoxEventCallback
		{
		protected:
			const CUIPage::EType mPageType;
		public:
			CUIPageLogic(CUIPage::EType pageType):mPageType(pageType){}
			virtual ~CUIPageLogic(){}
			CUIPage::EType getPageType()const
			{
				return mPageType;
			}
			// 通过 IButtonEventCallback 继承
			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e) override{}

			// 通过 IEditBoxEventCallback 继承
			virtual Void onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent e) override{}
		};
	}
}