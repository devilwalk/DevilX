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
		{
		protected:
			const String mServerIP;
			const UInt16 mServerPort;
			const String mClientIP;
			const UInt16 mClientPort;
			ILinkListener * mListener;
			TVector<Byte> mSendBuffer;
		public:
			ILinkImp(const String & serverIP,UInt16 serverPort,const String & clientIP,UInt16 clientPort);
			~ILinkImp();
			decltype(mSendBuffer) & getSendBufferRef()
			{
				return mSendBuffer;
			}
			Void addReceivedBuffer(ConstVoidPtr buffer,UInt32 bufferSizeInBytes);
			// Inherited via ILink
			virtual const String & getServerIP() const override;
			virtual UInt16 getServerPort() const override;
			virtual const String & getClientIP() const override;
			virtual UInt16 getClientPort() const override;
			virtual Void addSendData(ConstVoidPtr data,UInt32 sizeInBytes) override;
			virtual Void setListener(ILinkListener * listener);
			virtual ILinkListener * getListener()const;
		};
	}
}