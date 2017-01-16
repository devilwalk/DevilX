#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CTerrainGeneratorInstance
			:public ITerrainGeneratorInstance
		{
		protected:
			ITerrainGenerator * const mGenerator;
			ISceneManager *const  mSceneManager;
		public:
			CTerrainGeneratorInstance(ITerrainGenerator * generator,ISceneManager * sceneManager);
			~CTerrainGeneratorInstance();
			// Inherited via ITerrainGeneratorInstance
			virtual ITerrainGenerator * getGenerator() const override;
			virtual ISceneManager * getSceneManager() const override;
		};
	}
}