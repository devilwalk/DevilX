#pragma once
#include "ICubeBlockWorldTerrainGeneratorInstance.h"
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class IWorld;
		class ISceneManager;
		class ITerrainGenerator
		{
		protected:
			virtual ~ITerrainGenerator(){}
		public:
			virtual const String & getName()const=0;
			virtual ITerrainGeneratorInstance * createInstance(ISceneManager * sceneManager)=0;
			virtual Void destroyInstance(ITerrainGeneratorInstance * instance)=0;
		};
	}
}