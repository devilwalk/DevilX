#pragma once
#include "SceneLoader.h"
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CSceneManager
			:public ISceneManager
			,public TBaseObject<CSceneManager>
		{
		public:
			static const CUInt3 sChunkSize;
		protected:
			const String mName;
			NSRenderSystem::IScene * const mRenderScene;
			NSCubeBlockSystem::IScene * mBlockScene;
			ITerrainGeneratorInstance * mTerrainGeneratorInstance;
			CRange3I mRange;
			TNamedResourcePtrMap<CSceneLoader> mLoaders;
			TVectorMT<TVectorMT<TVectorMT<TSharedReadData<Int32>*>*>*> mChunkLoadeds[2][2][2];
		public:
			CSceneManager(const String & name,ITerrainGenerator * generator,NSRenderSystem::IScene * renderScene);
			~CSceneManager();
			Void update();
			Void loadChunkMT(DirectX::FXMVECTOR positionVec);
			Void unloadChunkMT(DirectX::FXMVECTOR positionVec);
			// Inherited via ISceneManager
			virtual ITerrainGeneratorInstance * getTerrainGenerator() const override;
			virtual const CUInt3 & getChunkSize() const override;
			virtual NSCubeBlockSystem::IScene * getScene() const override;
			virtual ISceneLoader * createLoader(const String & name) override;
			virtual ISceneLoader * getLoader(const String & name) const override;
			virtual Void destroyLoader(ISceneLoader * loader) override;
			virtual Void setRange(const CRange3I & range) override;
			virtual const CRange3I & getRange() const override;
		protected:
			TSharedReadData<Int32> * _getChunkLoaded(DirectX::FXMVECTOR positionVec);
		};
	}
}