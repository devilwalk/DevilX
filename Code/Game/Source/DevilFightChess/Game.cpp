#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CGame::CGame()
	:mViewport(nullptr)
	,mServerManager(nullptr)
	,mFontManager(nullptr)
	,mUIManager(nullptr)
	,mMatchServerManager(nullptr)
	,mGUIScene(nullptr)
{
	mViewport=CApp::getSingleton().getRenderWindow()->queryInterface_IRenderTarget()->createViewport("Main");
	registerModule(DEVILX_NEW CRegister);
	registerModule(DEVILX_NEW CLogin);
	registerModule(DEVILX_NEW CBigWorld);
	registerModule(DEVILX_NEW CMatchServerConfig);
}

NSDevilX::NSFightChess::CGame::~CGame()
{
	mModules.destroyAll();
	DEVILX_DELETE(mMatchServerManager);
	DEVILX_DELETE(mServerManager);
	DEVILX_DELETE(getUIManager());
	DEVILX_DELETE(mFontManager);
	NSGUISystem::getSystem()->destroyScene(getGUIScene());
}

Void NSDevilX::NSFightChess::CGame::initialize()
{
	mServerManager=DEVILX_NEW CServerManager;
	mFontManager=DEVILX_NEW CFontManager;
	mUIManager=DEVILX_NEW CUIManager;
	mMatchServerManager=DEVILX_NEW CMatchServerManager;
	mGUIScene=NSGUISystem::getSystem()->createScene(getViewport());

	startModule("Login");
}

Void NSDevilX::NSFightChess::CGame::registerModule(CModule * mod)
{
	mModules.add(mod->getName(),mod);
}

Void NSDevilX::NSFightChess::CGame::setModuleParameter(const String & moduleName,const String & name,const CAny & parameter)
{
	auto mod=mModules.get(moduleName);
	mod->setParameter(name,parameter);
}

Void NSDevilX::NSFightChess::CGame::startModule(const String & moduleName)
{
	auto mod=mModules.get(moduleName);
	mActiveModules.insert(mod);
	mod->start();
}

Void NSDevilX::NSFightChess::CGame::stopModule(const String & moduleName)
{
	auto mod=mModules.get(moduleName);
	mod->stop();
	mActiveModules.erase(mod);
}

Void NSDevilX::NSFightChess::CGame::update()
{
	TVector<CModule*> modules;
	for(auto mod:mActiveModules)
		modules.push_back(mod);
	for(auto mod:modules)
		mod->update();
}

Void NSDevilX::NSFightChess::CGame::messageBox(const CUTF8String & msg)
{
	DEVILX_NEW CMessageBox(msg);
}
