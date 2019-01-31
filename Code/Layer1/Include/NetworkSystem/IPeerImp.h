#pragma once
#include "ILinkImp.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ISystemImp;
		class IPeerImp
			:public IPeer
			,public TBaseObject<IPeerImp>
			,public TMessageReceiver<ISystemImp>
		{
		protected:
			const String mIP;
			const UInt16 mPort;
			String mConnectionKey;
			NSCore::INetworkHost * mHost;
			IPeerListener * mListener;
			TList<ILinkImp*> mLinks;
			TSet<NSCore::INetworkConnection*> mUnprocessedConnections;
		public:
			IPeerImp(const String & ip,UInt16 port);
			~IPeerImp();
			// ͨ�� IServer �̳�
			virtual const String & getIP() const override;
			virtual UInt16 getPort() const override;
			virtual Void setConnectKey(const String & key) override;
			virtual const String & getConnectKey() const override;
			virtual Void setListener(IPeerListener * listener) override;
			virtual IPeerListener * getListener() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}