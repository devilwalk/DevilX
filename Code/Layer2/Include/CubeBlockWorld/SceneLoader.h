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
			CInt3 mPosition;
			CUInt3 mSyncRange;
			CUInt3 mAsyncRange;
			CRange3I mLoadedRange;
		public:
			CSceneLoader(const String & name,CSceneManager * sceneManager);
			~CSceneLoader();
			// Inherited via ISceneLoader
			virtual const String & getName() const override;
			virtual Void setChunkPosition(const CInt3 & position) override;
			virtual Void setBlockPosition(const CInt3 & position) override;
			virtual const CInt3 & getChunkPosition() const override;
			virtual Void setSyncChunkRange(const CUInt3 & range) override;
			virtual const CUInt3 & getSyncChunkRange() const override;
			virtual Void setAsyncChunkRange(const CUInt3 & range) override;
			virtual const CUInt3 & getAsyncChunkRange() const override;
		};
	}
}