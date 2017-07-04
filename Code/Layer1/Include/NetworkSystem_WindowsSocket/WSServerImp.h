#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CServerImp
				:public TBaseObject<CServerImp>
				,public TMessageReceiver<CSystemImp>
			{
			protected:
				IServerImp * const mInterfaceImp;
				SOCKET mAcceptSocket;
				HANDLE mAcceptThreadHandle;
				TResourcePtrListMT<CLinker> mUnprocessedLinkers;
				TResourcePtrList<CLinker> mLinkers;
			public:
				CServerImp(IServerImp * interfaceImp);
				~CServerImp();
				IServerImp * getInterfaceImp()const
				{
					return mInterfaceImp;
				}
				SOCKET getAcceptSocket()const
				{
					return mAcceptSocket;
				}
				Void addUnprocessedLinkerMT(CLinker * linker);
			protected:
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}