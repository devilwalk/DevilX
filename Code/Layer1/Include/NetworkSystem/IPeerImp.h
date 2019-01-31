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
			// 通过 IServer 继承
			virtual const String & getIP() const override;
			virtual UInt16 getPort() const override;
			virtual Void setConnectKey(const String & key) override;
			virtual const String & getConnectKey() const override;
			virtual Void setListener(IPeerListener * listener) override;
			virtual IPeerListener * getListener() const override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}