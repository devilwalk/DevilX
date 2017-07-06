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
					DWORD mIOSize;
					DWORD mFlag;
					SIOComplete(EType type)
						:mType(type)
						,mIOSize(0)
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
						DEVILX_FREE(mBuffer.buf);
					}
				};
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