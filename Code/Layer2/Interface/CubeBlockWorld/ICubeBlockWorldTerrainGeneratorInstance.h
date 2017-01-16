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
			virtual NSCubeBlockSystem::IBlock * generateBlock(DirectX::XMVECTOR positionVec)=0;
			virtual Boolean generateChunk(DirectX::XMVECTOR positionVec)=0;
		};
	}
}