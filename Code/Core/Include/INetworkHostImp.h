#pragma once
#include "NetworkAcceptor.h"
#include "INetworkConnectionImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkHostImp
			:public TBaseObject<INetworkHostImp>
			,public INetworkHost
			,public TMessageReceiver<CNetworkAcceptor>
			,public TMessageReceiver<INetworkConnectionImp>
		{
		protected:
			const String mIP;
			TResourcePtrMap(UInt16,CNetworkAcceptor) mAcceptors;
			TList(INetworkConnectionImp*) mConnections;
		public:
			INetworkHostImp(const String & ip);
			~INetworkHostImp();

			// Í¨¹ý INetworkHost ¼Ì³Ð
			virtual ConstCharPtr getIP() const override;
			virtual Void addListeningPort(UInt16 port) override;
			virtual Void removeListeningPort(UInt16 port) override;
			virtual Void createOrRetrieveConnection(ConstCharPtr endPointIP,UInt16 endPointPort,UInt16 hostPort=0) override;
			virtual SizeT getNumConnections() const override;
			virtual INetworkConnection * getConnection(SizeT index) const override;

			virtual Void onMessage(CNetworkAcceptor * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(INetworkConnectionImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}