#pragma once
#include "ICubeBlockWorldTerrainGeneratorInstance.h"
#include "ICubeBlockWorldSceneLoader.h"
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class ISceneManager
		{
		protected:
			virtual ~ISceneManager(){}
		public: 
			virtual ITerrainGeneratorInstance * getTerrainGenerator()const=0;
			virtual const CSInt3 & getChunkSize()const=0;
			virtual NSCubeBlockSystem::IScene * getScene()const=0;
			virtual ISceneLoader * createLoader(const String & name)=0;
			virtual ISceneLoader * getLoader(const String & name)const=0;
			virtual Void destroyLoader(ISceneLoader * loader)=0;
			virtual Void setRange(const CRange3I & range)=0;
			virtual const CRange3I & getRange()const=0;
		};
	}
}