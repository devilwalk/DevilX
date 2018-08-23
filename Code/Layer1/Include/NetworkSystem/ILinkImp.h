#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IPeerImp;
		class ILinkImp
			:public ILink
			,public TBaseObject<ILinkImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Destruction,
			};
		protected:
			IPeerImp*const mPeer;
			NSCore::INetworkConnection * const mConnection;
			String mRemoteIP;
			ILinkListener * mListener;
		public:
			ILinkImp(IPeerImp * peer,NSCore::INetworkConnection * connection);
			~ILinkImp();
			// Inherited via ILink
			virtual IPeer * getPeer() const override;
			virtual const String & getRemoteIP() const override;
			virtual UInt16 getRemotePort() const override;
			virtual Void addSendData(ConstVoidPtr data,UInt32 sizeInBytes) override;
			virtual Void setListener(ILinkListener * listener);
			virtual ILinkListener * getListener()const;
		};
	}
}