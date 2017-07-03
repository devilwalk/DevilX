#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IServerImp;
		class IClientImp;
		class ILinkImp
			:public ILink
			,public TBaseObject<ILinkImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginPushSendData,
				EMessage_EndPushSendData
			};
		protected:
			const String mServerIP;
			const UInt16 mServerPort;
			const String mClientIP;
			const UInt16 mClientPort;
			TList<TVector<Byte> > mSendDatas;
			TList<TVector<Byte> > mReceiveDatas;
		public:
			ILinkImp(const String & serverIP,UInt16 serverPort,const String & clientIP,UInt16 clientPort);
			~ILinkImp();
			decltype(mSendDatas) & getSendDatas()
			{
				return mSendDatas;
			}
			Void addReceiveData(const decltype(mReceiveDatas)::value_type & data)
			{
				mReceiveDatas.push_back(data);
			}
			// Inherited via ILink
			virtual const String & getServerIP() const override;
			virtual UInt16 getServerPort() const override;
			virtual const String & getClientIP() const override;
			virtual UInt16 getClientPort() const override;
			virtual Void pushSendData(ConstVoidPtr data,UInt32 sizeInBytes) override;
			virtual UInt32 getFirstReceiveDataSizeInBytes() const override;
			virtual Void popReceiveData(VoidPtr data) override;
		};
	}
}