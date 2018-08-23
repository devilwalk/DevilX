#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkHostImp;
		class INetworkConnectionImp
			:public INetworkConnection
			,public TBaseObject<INetworkConnectionImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction
			};
		protected:
			INetworkHostImp*const mHost;
			asio::ip::tcp::socket * const mSocket;
			Bool mValidate;
			TVector(Byte) mReceives;
			TVector(Byte) mReceiveTemp;
		public:
			INetworkConnectionImp(INetworkHostImp * host,asio::ip::tcp::socket * s);
			~INetworkConnectionImp();

			// Í¨¹ý INetworkConnection ¼Ì³Ð
			virtual Boolean isValidate() const override;
			virtual INetworkHost * getHost() const override;
			virtual UInt16 getHostPort() const override;
			virtual ConstCharPtr getEndPointIP() const override;
			virtual UInt16 getEndPointPort() const override;
			virtual void send(ConstVoidPtr data,SizeT sizeInBytes) override;
			virtual ConstVoidPtr getReceivedData() const override;
			virtual SizeT getReceivedSizeInBytes() const override;
			virtual Void received(SizeT sizeInBytes) override;
		protected:
			static Void _read(INetworkConnectionImp * connection,const asio::error_code& error,std::size_t bytes_transferred);
		};
	}
}