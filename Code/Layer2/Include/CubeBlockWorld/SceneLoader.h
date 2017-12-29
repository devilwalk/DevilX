#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CSceneManager;
		class CSceneLoader
			:public ISceneLoader
			,public TBaseObject<CSceneLoader>
			,public CDirtyFlagContainer
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Load
			};
		protected:
			const String & mName;
			CSceneManager * const mSceneManager;
			CThreadPool * mThreadPool;
			CInt3 mPosition;
			CInt3 mRange;
			CRange3I mLoadedRange;
		public:
			CSceneLoader(const String & name,CSceneManager * sceneManager);
			~CSceneLoader();
			Void update();
			// Inherited via ISceneLoader
			virtual const String & getName() const override;
			virtual Void setChunkPosition(const CInt3 & position) override;
			virtual Void setBlockPosition(const CInt3 & position) override;
			virtual const CInt3 & getChunkPosition() const override;
			virtual Void setChunkRange(const CInt3 & range) override;
			virtual const CInt3 & getChunkRange() const override;

			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
		protected:
			Void _processLoad();
		};
	}
}