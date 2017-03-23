#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class ITerrainGenerator;
		class ISceneManager;
		class ITerrainGeneratorInstance
		{
		protected:
			virtual ~ITerrainGeneratorInstance(){}
		public:
			virtual ITerrainGenerator * getGenerator()const=0;
			virtual ISceneManager * getSceneManager()const=0;
			virtual NSCubeBlockSystem::IBlock * generateBlock(const CInt3 & position)=0;
			virtual Boolean generateChunk(const CInt3 & position)=0;
		};
	}
}