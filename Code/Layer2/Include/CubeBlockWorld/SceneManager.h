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
			struct SChunkState
				:public TBaseObject<SChunkState>
			{
				enum EState
				{
					EState_Prepare,
					EState_Loading,
					EState_PreLoaded,
					EState_Loaded,
					EState_Unloading
				};
				TSharedReadData<EState> mState;
				TMap<NSCubeBlockSystem::IBlock*,TVector<CRange3I> > mPreLoads;
				SChunkState()
					:mState(EState_Loading)
				{}
			};
			struct SInt3Comparator
			{
			public:
				Boolean operator()(const CInt3 & key1,const CInt3 & key2)const
				{
					if(key1.x!=key2.x)
					{
						return key1.x<key2.x;
					}
					else
					{
						if(key1.y!=key2.y)
						{
							return key1.y<key2.y;
						}
						else
						{
							return key1.z<key2.z;
						}
					}
				}
			};
			static const CUInt3 sChunkSize;
		protected:
			const String mName;
			CThreadPool * mLoadThreadPool;
			NSRenderSystem::IScene * const mRenderScene;
			NSCubeBlockSystem::IScene * mBlockScene;
			ITerrainGeneratorInstance * mTerrainGeneratorInstance;
			CRange3I mRange;
			TNamedResourcePtrMap<CSceneLoader> mLoaders;
			TMap<CInt3,SChunkState*,SInt3Comparator> mChunkLoadStates;
		public:
			CSceneManager(const String & name,ITerrainGenerator * generator,NSRenderSystem::IScene * renderScene);
			~CSceneManager();
			CThreadPool * getLoadThreadPool()const
			{
				return mLoadThreadPool;
			}
			Void update();
			// Inherited via ISceneManager
			virtual ITerrainGeneratorInstance * getTerrainGenerator() const override;
			virtual const CUInt3 & getChunkSize() const override;
			virtual NSCubeBlockSystem::IScene * getScene() const override;
			virtual ISceneLoader * createLoader(const String & name) override;
			virtual ISceneLoader * getLoader(const String & name) const override;
			virtual Void destroyLoader(ISceneLoader * loader) override;
			virtual Void setRange(const CRange3I & range) override;
			virtual const CRange3I & getRange() const override;
		};
	}
}