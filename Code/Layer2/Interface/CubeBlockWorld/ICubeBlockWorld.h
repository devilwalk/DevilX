#pragma once
#include "ICubeBlockWorldSceneManager.h"
#include "ICubeBlockWorldTerrainGenerator.h"
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class IWorld
		{
		protected:
			virtual ~IWorld(){}
		public:
			virtual Void registerTerrainGenerator(ITerrainGenerator * generator)=0;
			virtual ITerrainGenerator * getTerrainGenerator(const String & name)const=0;
			virtual UInt32 getTerrainGeneratorsCount()const=0;
			virtual ITerrainGenerator * getTerrainGenerator(UInt32 index)const=0;
			virtual ISceneManager * createSceneManager(const String & name,ITerrainGenerator * generator,NSRenderSystem::IScene * renderScene)=0;
			virtual ISceneManager * getSceneManager(const String & name)const=0;
			virtual Void destroySceneManager(const String & name)=0;
			virtual ISceneManager * load(const String & name,const String & configFileName,NSRenderSystem::IScene * renderScene)=0;
			virtual Void save(ISceneManager * sceneManager)=0;
			virtual Void update()=0;
			virtual Void shutdown()=0;
			virtual Void loadTerrainGeneratorPlugin(const String & pluginFullName)=0;
			virtual Void loadWorld(const String & fullName)=0;
		};
		IWorld * getWorld();
	}
}