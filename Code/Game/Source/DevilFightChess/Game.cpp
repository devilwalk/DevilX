#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CGame::CGame()
	:mViewport(nullptr)
	,mServerManager(nullptr)
	,mFontManager(nullptr)
	,mGUIScene(nullptr)
{
	mViewport=CApp::getSingleton().getRenderWindow()->queryInterface_IRenderTarget()->createViewport("Main");
	registerModule(DEVILX_NEW CRegister);
	registerModule(DEVILX_NEW CLogin);
}

NSDevilX::NSFightChess::CGame::~CGame()
{
	DEVILX_DELETE(mServerManager);
	DEVILX_DELETE(mFontManager);
	NSGUISystem::getSystem()->destroyScene(getGUIScene());
}

Void NSDevilX::NSFightChess::CGame::initialize()
{
	mServerManager=DEVILX_NEW CServerManager;
	mFontManager=DEVILX_NEW CFontManager;
	mGUIScene=NSGUISystem::getSystem()->createScene(getViewport());

	startModule("Login");
}

Void NSDevilX::NSFightChess::CGame::registerModule(CModule * module)
{
	mModules.add(module->getName(),module);
}

Void NSDevilX::NSFightChess::CGame::startModule(const String & moduleName)
{
	auto module=mModules.get(moduleName);
	mActiveModules.insert(module);
	module->start();
}

Void NSDevilX::NSFightChess::CGame::stopModule(const String & moduleName)
{
	auto module=mModules.get(moduleName);
	module->stop();
	mActiveModules.erase(module);
}

Void NSDevilX::NSFightChess::CGame::update()
{
	TVector<CModule*> modules;
	for(auto module:mActiveModules)
		modules.push_back(module);
	for(auto module:modules)
		module->update();
}
