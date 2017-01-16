#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;

NSDevilX::NSCubeBlockWorld::IWorld * NSDevilX::NSCubeBlockWorld::getWorld()
{
	if(!CWorld::getSingletonPtr())
		DEVILX_NEW CWorld;
	return CWorld::getSingletonPtr();
}

NSDevilX::NSCubeBlockWorld::CWorld::CWorld()
	:mCurrentWorldDirectory(nullptr)
{
	_loadDefaultTerrainGenerator();
}

NSDevilX::NSCubeBlockWorld::CWorld::~CWorld()
{
	for(auto plugin:mPlugins)
		DEVILX_DELETE(plugin);
}

Void NSDevilX::NSCubeBlockWorld::CWorld::registerTerrainGenerator(ITerrainGenerator * generator)
{
	mTerrainGenerators.add(generator->getName(),generator);
}

ITerrainGenerator * NSDevilX::NSCubeBlockWorld::CWorld::getTerrainGenerator(const String & name) const
{
	if(mTerrainGenerators.has(name))
		return mTerrainGenerators.get(name);
	else
		return nullptr;
}

UInt32 NSDevilX::NSCubeBlockWorld::CWorld::getTerrainGeneratorsCount() const
{
	return static_cast<UInt32>(mTerrainGenerators.size());
}

ITerrainGenerator * NSDevilX::NSCubeBlockWorld::CWorld::getTerrainGenerator(UInt32 index) const
{
	return mTerrainGenerators.get(index);
}

ISceneManager * NSDevilX::NSCubeBlockWorld::CWorld::createSceneManager(const String & name,ITerrainGenerator * generator,NSRenderSystem::IScene * renderScene)
{
	if(getSceneManager(name))
		return nullptr;
	auto sm=DEVILX_NEW CSceneManager(name,generator,renderScene);
	mSceneManagers.add(name,sm);
	return sm;
}

ISceneManager * NSDevilX::NSCubeBlockWorld::CWorld::getSceneManager(const String & name) const
{
	return mSceneManagers.get(name);
}

Void NSDevilX::NSCubeBlockWorld::CWorld::destroySceneManager(const String & name)
{
	mSceneManagers.destroy(name);
}

ISceneManager * NSDevilX::NSCubeBlockWorld::CWorld::load(const String & name,const String & configFileName,NSRenderSystem::IScene * renderScene)
{
	return nullptr;
}

Void NSDevilX::NSCubeBlockWorld::CWorld::save(ISceneManager * sceneManager)
{
	return Void();
}

Void NSDevilX::NSCubeBlockWorld::CWorld::update()
{
	for(auto const & sm:mSceneManagers)
		sm.second->update();
	NSCubeBlockSystem::getSystem()->update();
}

Void NSDevilX::NSCubeBlockWorld::CWorld::shutdown()
{
	DEVILX_DELETE(this);
}

Void NSDevilX::NSCubeBlockWorld::CWorld::loadTerrainGeneratorPlugin(const String & pluginFullName)
{
	auto plug=DEVILX_NEW CModule(pluginFullName);
	typedef Boolean(*install_func)(IWorld *,NSCubeBlockSystem::ISystem *);
	auto func=reinterpret_cast<install_func>(plug->getProcAddress("install"));
	func(this,NSCubeBlockSystem::getSystem());
	mPlugins.push_back(plug);
}

Void NSDevilX::NSCubeBlockWorld::CWorld::loadWorld(const String & fullName)
{
	DEVILX_DELETE(mCurrentWorldDirectory);
	mCurrentWorldDirectory=DEVILX_NEW CDirectory(CDirectory::getAbsolutePath(fullName));
	mCurrentWorldDirectory->create();
	//½âÎöconfig
	_loadWorldConfig();
}

Void NSDevilX::NSCubeBlockWorld::CWorld::_loadDefaultTerrainGenerator()
{
	loadTerrainGeneratorPlugin("CubeBlockWorldTerrainGenerator");
}

Void NSDevilX::NSCubeBlockWorld::CWorld::_loadWorldConfig()
{
	CDirectory dir("Config",mCurrentWorldDirectory);
	dir.create();
	TiXmlDocument doc;
	if(doc.LoadFile((dir.getFullName()+"/world.xml").c_str()))
	{

	}
}
