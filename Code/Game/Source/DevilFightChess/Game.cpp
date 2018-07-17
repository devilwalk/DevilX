#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CGame::CGame()
	:mViewport(nullptr)
	,mLogic(nullptr)
	,mServerManager(nullptr)
	,mFontManager(nullptr)
	,mUIManager(nullptr)
	,mMatchServerManager(nullptr)
	,mGUIScene(nullptr)
{
	mViewport=CApp::getSingleton().getRenderWindow()->queryInterface_IRenderTarget()->createViewport("Main");
	registerModule(DEVILX_NEW CRegister);
	registerModule(DEVILX_NEW CLogin);
}

NSDevilX::NSFightChess::CGame::~CGame()
{
	mModules.destroyAll();
	DEVILX_DELETE(mLogic);
	DEVILX_DELETE(mMatchServerManager);
	DEVILX_DELETE(mServerManager);
	DEVILX_DELETE(getUIManager());
	DEVILX_DELETE(mFontManager);
	NSGUISystem::getSystem()->destroyScene(getGUIScene());
}

Void NSDevilX::NSFightChess::CGame::initialize()
{
	mLogic=DEVILX_NEW CGameLogic;
	mServerManager=DEVILX_NEW CServerManager;
	mFontManager=DEVILX_NEW CFontManager;
	mUIManager=DEVILX_NEW CUIManager;
	mMatchServerManager=DEVILX_NEW CMatchServerManager;
	mGUIScene=NSGUISystem::getSystem()->createScene(getViewport());

	auto page=getUIManager()->createOrRetrievePage(CUIPage::EType_Login);
	page->setButtonLogic(CLoginPageLogic::buttonLogic);
}

Void NSDevilX::NSFightChess::CGame::registerModule(CModule * mod)
{
	mModules.add(mod->getName(),DEVILX_NEW SModule(mod));
}

Void NSDevilX::NSFightChess::CGame::setModuleParameter(const String & moduleName,const String & name,const CAny & parameter)
{
	auto mod=mModules.get(moduleName);
	mod->mModule->setParameter(name,parameter);
}

Void NSDevilX::NSFightChess::CGame::startModule(const String & moduleName)
{
	auto mod=mModules[moduleName];
	mod->mActived=True;
	mod->mModule->start();
}

Void NSDevilX::NSFightChess::CGame::stopModule(const String & moduleName)
{
	auto mod=mModules[moduleName];
	mod->mModule->stop();
	mod->mActived=False;
}

Void NSDevilX::NSFightChess::CGame::update()
{
	for(auto const & mod:mModules)
		if(mod.second->mActived)
			mod.second->mModule->update();
}

Void NSDevilX::NSFightChess::CGame::messageBox(const CUTF8String & msg)
{
	DEVILX_NEW CMessageBox(msg);
}
