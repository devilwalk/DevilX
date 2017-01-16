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
			const String mName;
			const String mDestination;
			TList<TVector<Byte> > mSendDatas;
			TList<TVector<Byte> > mReceiveDatas;
		public:
			ILinkImp(const String & name,const String & destIP);
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
			virtual const String & getName() const override;
			virtual const String & getDestination() const override;
			virtual Void pushSendData(ConstBytePtr data,UInt32 sizeInBytes) override;
			virtual UInt32 getFirstReceiveDataSizeInBytes() const override;
			virtual Void popReceiveData(BytePtr data) override;
		};
	}
}