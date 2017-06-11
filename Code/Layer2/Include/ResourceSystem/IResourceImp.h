#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class ISystemImp;
		class IResourceImp
			:public TBaseObject<IResourceImp>
			,public IResource
			,public ILoadedResource
			,public TMessageReceiver<ISystemImp>
			,public CUserDataContainer
		{
		public:
			enum ELoadState
			{
				ELoadState_Unload,
				ELoadState_Loading,
				ELoadState_Loaded
			};
		protected:
			const String mName;
			const String mFile;
			ELoadState mLoadState;
			TVector<ILoadCallback*> mLoadCallbacks;
			Int32 mLoadThreadSyncGroupID;
			TSharedReadData<CMemoryStream*> mBuffer;
		public:
			IResourceImp(const String & name,const String & file);
			~IResourceImp();
			Void setDataStreamMT(CMemoryStream * stream);
			CMemoryStream * getBuffer()
			{
				return mBuffer;
			}
			// 通过 IResource 继承
			virtual const String & getName() const override;
			virtual const String & getFileName() const override;
			virtual Void load(ILoadCallback * callback,Bool sync) override;
			virtual Boolean isLoaded() const override;

			// 通过 ILoadedResource 继承
			virtual IResource * queryInterface_IResource() const override;
		protected:
			Void _updateLoadState();

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}