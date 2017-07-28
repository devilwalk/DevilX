#pragma once
#include "UIPageLogic.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIPage
			:public TBaseObject<CUIPage>
		{
		public:
			enum EType
			{
				EType_Login,
				EType_Register,
				EType_BigWorld,
				EType_MatchServerConfig,
				EType_Count
			};
		protected:
			EType const mType;
			NSGUISystem::IWindow * mGUIWindow;
			CUIPageLogic * mPageLogic;
		public:
			CUIPage(EType type);
			virtual ~CUIPage();
			EType getType()const
			{
				return mType;
			}
			NSGUISystem::IWindow * getGUIWindow()const
			{
				return mGUIWindow;
			}
			Void setPageLogic(CUIPageLogic * logic);
		};
	}
}