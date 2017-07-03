#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CServerImp
				:public TInterfaceObject<IServerImp>
				,public TBaseObject<CServerImp>
			{
			protected:
				SOCKET mAcceptSocket;
				HANDLE mAcceptThreadHandle;
				TResourcePtrListMT<CLinker> mUnprocessedLinkers;
			public:
				CServerImp(IServerImp * interfaceImp);
				~CServerImp();
				SOCKET getAcceptSocket()const
				{
					return mAcceptSocket;
				}
				Void addLinkerMT(CLinker * linker);
			protected:
				Void _processUnprocessedLinkers();

				// ͨ�� TInterfaceObject �̳�
				virtual Void onMessage(IServerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}