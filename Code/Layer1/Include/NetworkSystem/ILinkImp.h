#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
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
			const String mDestination;
			const UInt16 mPort;
			TList<TVector<Byte> > mSendDatas;
			TList<TVector<Byte> > mReceiveDatas;
		public:
			ILinkImp(const String & destIP,UInt16 port);
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
			virtual const String & getDestination() const override;
			virtual UInt16 getPort() const override;
			virtual Void pushSendData(ConstVoidPtr data,UInt32 sizeInBytes) override;
			virtual UInt32 getFirstReceiveDataSizeInBytes() const override;
			virtual Void popReceiveData(VoidPtr data) override;
		};
	}
}