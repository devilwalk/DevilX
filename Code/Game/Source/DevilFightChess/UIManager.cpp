#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CUIManager::CUIManager()
{
	mPageLogics[CUIPage::EType_Login]=DEVILX_NEW CLoginPageLogic();
	mPageResouceLocations[CUIPage::EType_Login]=CDirectory::getApplicationDirectory()+"/Resource/""Login""Page.layout";
	mPageResouceLocations[CUIPage::EType_Register]=CDirectory::getApplicationDirectory()+"/Resource/""Register""Page.layout";
	mPageResouceLocations[CUIPage::EType_BigWorld]=CDirectory::getApplicationDirectory()+"/Resource/""BigWorld""Page.layout";
	mPageResouceLocations[CUIPage::EType_MatchServerConfig]=CDirectory::getApplicationDirectory()+"/Resource/""MatchServerConfig""Page.layout";
	mPages.resize(CUIPage::EType_Count);
}

NSDevilX::NSFightChess::CUIManager::~CUIManager()
{}

CUIPage * NSDevilX::NSFightChess::CUIManager::createPage(CUIPage::EType type)
{
	if(getPage(type))
		return nullptr;
	auto ret=DEVILX_NEW CUIPage(type);
	mPages[type]=ret;
	ret->setPageLogic(mPageLogics[type]);
	return ret;
}

CUIPage * NSDevilX::NSFightChess::CUIManager::getPage(CUIPage::EType type) const
{
	return mPages[type];
}

CUIPage * NSDevilX::NSFightChess::CUIManager::createOrRetrievePage(CUIPage::EType type)
{
	if(getPage(type))
		return getPage(type);
	mPages[type]=DEVILX_NEW CUIPage(type);
	return getPage(type);
}

Void NSDevilX::NSFightChess::CUIManager::destroyPage(CUIPage::EType type)
{
	DEVILX_DELETE(getPage(type));
	mPages[type]=nullptr;
}