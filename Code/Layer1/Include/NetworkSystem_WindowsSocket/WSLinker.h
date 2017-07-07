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
			public:
				struct SIOComplete
					:public TBaseObject<SIOComplete>
				{
					enum EType
					{
						EType_Recv,
						EType_Send
					};
					const EType mType;
					WSABUF mBuffer;
					DWORD mFlag;
					SIOComplete(EType type)
						:mType(type)
						,mFlag(0)
					{
						switch(type)
						{
						case EType_Recv:
							mBuffer.buf=static_cast<decltype(mBuffer.buf)>(DEVILX_ALLOC(UINT16_MAX+32));
							SecureZeroMemory(mBuffer.buf,UINT16_MAX+32);
							mBuffer.len=UINT16_MAX+32;
							break;
						case EType_Send:
							mBuffer.buf=nullptr;
							mBuffer.buf=0;
							break;
						}
					}
					~SIOComplete()
					{
						switch(mType)
						{
						case EType_Recv:
							DEVILX_FREE(mBuffer.buf);
							break;
						}
					}
				};
			protected:
				volatile SOCKET mSocket;
				volatile Bool mDisconnect;
				String mDestIP;
				UInt16 mDestPort;
				WSAOVERLAPPED mWriteOverlapped;
				WSAOVERLAPPED mReadOverlapped;
				TVectorMT<Byte> mSendBufferCache;
				TVectorMT<Byte> mRecvBufferCache;
				TVector<Char> mSendBuffer;
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
				WSAOVERLAPPED & getWriteOverlappedRef()
				{
					return mWriteOverlapped;
				}
				WSAOVERLAPPED & getReadOverlappedRef()
				{
					return mReadOverlapped;
				}
				decltype(mRecvBufferCache) & getRecvBufferCache()
				{
					return mRecvBufferCache;
				}
				Void addSendData(ConstVoidPtr data,SizeT sizeInBytes);
				Void addRecvData(ConstVoidPtr data,SizeT sizeInBytes);
				Void send();
				Void receive();
				Void disconnect();
			};
		}
	}
}