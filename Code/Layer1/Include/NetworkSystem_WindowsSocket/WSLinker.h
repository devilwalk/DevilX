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
			{
			protected:
				volatile SOCKET mSocket;
				volatile Bool mDisconnect;
				HANDLE mReadThread,mWriteThread;
				HANDLE mWriteThreadEvent;
				String mDestIP;
				UInt16 mDestPort;
				TVectorMT<Byte> mSendBuffer;
				TVectorMT<Byte> mRecvBuffer;
			public:
				CLinker(SOCKET s);
				virtual ~CLinker();
				SOCKET getSocket()const
				{
					return mSocket;
				}
				Bool isDisconnect()const
				{
					return mDisconnect;
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
				decltype(mSendBuffer) & getSendBuffer()
				{
					return mSendBuffer;
				}
				Void addRecvData(ConstVoidPtr data,SizeT sizeInBytes);
				decltype(mRecvBuffer) & getReceivedBuffer()
				{
					return mRecvBuffer;
				}
				Void disconnect();
			};
		}
	}
}