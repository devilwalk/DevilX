#pragma once
#include "Base.h"
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CSimpleTerrainGenertor;
		class CSimpleTerrainGeneratorInstance
			:public CTerrainGeneratorInstance
			,public TBaseObject<CSimpleTerrainGeneratorInstance>
		{
		protected:
		public:
			CSimpleTerrainGeneratorInstance(CSimpleTerrainGenertor * generator,ISceneManager * sceneManager);
			~CSimpleTerrainGeneratorInstance();

			// Inherited via ITerrainGeneratorInstance
			virtual NSCubeBlockSystem::IBlock * generateBlock(DirectX::XMVECTOR positionVec) override;
			virtual Boolean generateChunk(DirectX::XMVECTOR positionVec) override;
		};
		class CSimpleTerrainGenertor
			:public ITerrainGenerator
			,public TSingleton<CSimpleTerrainGenertor>
			,public TBaseObject<CSimpleTerrainGenertor>
		{
		protected:
			const String mName;
		public:
			CSimpleTerrainGenertor();
			~CSimpleTerrainGenertor();

			// Inherited via ITerrainGenerator
			virtual const String & getName() const override;
			virtual ITerrainGeneratorInstance * createInstance(ISceneManager * sceneManager) override;
			virtual Void destroyInstance(ITerrainGeneratorInstance * instance) override;
		};
	}
}