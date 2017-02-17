#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CWorld
			:public TBaseObject<CWorld>
			,public TSingleton<CWorld>
			,public IWorld
		{
		protected:
			CDirectory * mCurrentWorldDirectory;
			TVector<CModule*> mPlugins;
			TBaseNamedIndexResourcePtrContainer<ITerrainGenerator> mTerrainGenerators;
			TNamedResourcePtrMap<CSceneManager> mSceneManagers;
		public:
			CWorld();
			~CWorld();

			// Inherited via IWorld
			virtual Void registerTerrainGenerator(ITerrainGenerator * generator) override;
			virtual ITerrainGenerator * getTerrainGenerator(const String & name) const override;
			virtual UInt32 getTerrainGeneratorsCount() const override;
			virtual ITerrainGenerator * getTerrainGenerator(UInt32 index) const override;
			virtual ISceneManager * createSceneManager(const String & name,ITerrainGenerator * generator,NSRenderSystem::IScene * renderScene) override;
			virtual ISceneManager * getSceneManager(const String & name) const override;
			virtual Void destroySceneManager(const String & name) override;
			virtual ISceneManager * load(const String & name,const String & configFileName,NSRenderSystem::IScene * renderScene) override;
			virtual Void save(ISceneManager * sceneManager) override;
			virtual Void update() override;
			virtual Void shutdown() override;
			virtual Void loadTerrainGeneratorPlugin(const String & pluginFullName) override;
			virtual Void loadWorld(const String & fullName) override;
		protected:
			Void _loadDefaultTerrainGenerator();
			Void _loadWorldConfig();
		};
	}
}