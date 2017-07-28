#pragma once
#include "UIPage.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIManager
			:public TBaseObject<CUIManager>
		{
		public:

		protected:
			std::array<String,CUIPage::EType_Count> mPageResouceLocations;
			TResourcePtrVector<CUIPageLogic> mPageLogics;
			TResourcePtrVector<CUIPage> mPages;
		public:
			CUIManager();
			~CUIManager();
			const String & getPageResourceLocation(CUIPage::EType type)const
			{
				mPageResouceLocations[type];
			}
			CUIPage * createPage(CUIPage::EType type);
			CUIPage * getPage(CUIPage::EType type)const;
			CUIPage * createOrRetrievePage(CUIPage::EType type);
			Void destroyPage(CUIPage::EType type);
		};
	}
}