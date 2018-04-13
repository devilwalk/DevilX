#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class ISystemImp;
		class CResource
			:public TMessageReceiver<ISystemImp>
			,public CUserDataContainer
		{
		public:
			struct SLoadCallback
			{
				virtual Void onLoaded(CResource * res)=0;
			};
			enum ELoadState
			{
				ELoadState_Unload,
				ELoadState_Loading,
				ELoadState_Loaded
			};
		protected:
			ELoadState mLoadState;
			TVector<SLoadCallback*> mLoadCallbacks;
			Int32 mLoadThreadSyncGroupID;
			TSharedReadData<ELoadState*> mReplacedLoadStateMT;
		public:
			CResource();
			virtual ~CResource();
			Void load(SLoadCallback * callback,Bool sync);
			Boolean isLoaded() const;
		protected:
			Void _updateLoadState();
			virtual Boolean _loadImpMT()=0;

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}