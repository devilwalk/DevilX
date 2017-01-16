#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CSceneManager;
		class CSceneLoader
			:public ISceneLoader
			,public TBaseObject<CSceneLoader>
		{
		protected:
			const String & mName;
			CSceneManager * const mSceneManager;
			CThreadPool * mThreadPool;
			CSInt3 mPosition;
			CSInt3 mRange;
			CRange3I mLoadedRange;
		public:
			CSceneLoader(const String & name,CSceneManager * sceneManager);
			~CSceneLoader();
			Void update();
			// Inherited via ISceneLoader
			virtual const String & getName() const override;
			virtual Void setChunkPosition(DirectX::FXMVECTOR positionVec) override;
			virtual Void setBlockPosition(DirectX::FXMVECTOR positionVec) override;
			virtual const CSInt3 & getChunkPosition() const override;
			virtual Void setChunkRange(const CSInt3 & range) override;
			virtual const CSInt3 & getChunkRange() const override;
		};
	}
}