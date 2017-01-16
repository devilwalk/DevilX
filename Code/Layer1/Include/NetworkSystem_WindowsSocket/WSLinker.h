#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CLinker
				:public TBaseObject<CLinker>
				,public TMessageReceiver<ISystemImp>
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BeginDestruction,
					EMessage_EndDestruction
				};
			protected:
				volatile SOCKET mSocket;
				volatile Bool mDisconnect;
				HANDLE mReadThread,mWriteThread;
				TListMT<TVector<Byte> > mSendDatas;
				TVectorMT<TVector<Byte> > mRecvDatas;
			public:
				CLinker(SOCKET s,ConstVoidPtr initData=nullptr,SizeT dataSizeInBytes=0);
				virtual ~CLinker();
				SOCKET getSocket()const
				{
					return mSocket;
				}
				Void addSendData(ConstVoidPtr data,SizeT sizeInBytes);
				decltype(mSendDatas) & getSendDatas()
				{
					return mSendDatas;
				}
				Void addRecvData(ConstVoidPtr data,SizeT sizeInBytes);
				decltype(mRecvDatas) & getReceiveDatas()
				{
					return mRecvDatas;
				}
				Void disconnect();

				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}