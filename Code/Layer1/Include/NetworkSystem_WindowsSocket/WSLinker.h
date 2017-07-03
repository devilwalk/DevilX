#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CSystemImp;
			class CLinker
				:public TBaseObject<CLinker>
				,public CMessageNotifier
				,public TMessageReceiver<CSystemImp>
			{
			public:
				enum EMessage
				{
					EMessage_Disconnect
				};
			protected:
				volatile SOCKET mSocket;
				volatile Bool mDisconnect;
				HANDLE mReadThread,mWriteThread;
				HANDLE mWriteThreadEvent;
				String mDestIP;
				UInt16 mDestPort;
				TListMT<TVector<Byte> > mSendDatas;
				TVectorMT<TVector<Byte> > mRecvDatas;
			public:
				CLinker(SOCKET s);
				virtual ~CLinker();
				SOCKET getSocket()const
				{
					return mSocket;
				}
				const String & getDestIP()const
				{
					return mDestIP;
				}
				UInt16 getDestPort()const
				{
					return mDestPort;
				}
				HANDLE getWriteThreadEvent()const
				{
					return mWriteThreadEvent;
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
				Void setActive(Boolean active);
				Boolean isActive()const;
			};
		}
	}
}