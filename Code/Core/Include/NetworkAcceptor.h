#pragma once
#include "Socket.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CNetworkAcceptor
			:public TBaseObject<CNetworkAcceptor>
		{
		public:
		protected:
			asio::ip::tcp::acceptor mInternalV4;
			asio::ip::tcp::acceptor mInternalV6;
			TVector<std::shared_ptr<asio::ip::tcp::socket> > mConnectedSockets;
		public:
			CNetworkAcceptor(UInt16 port);
			~CNetworkAcceptor();
			UInt16 getPort()const{ return mInternalV4.local_endpoint().port(); }
			decltype(mConnectedSockets) const & getConnectedSockets()const{ return mConnectedSockets; }
			decltype(mConnectedSockets) & getConnectedSocketsRef(){ return mConnectedSockets; }
		protected:
			Void _acceptV4();
			Void _acceptV6();
		};
	}
}