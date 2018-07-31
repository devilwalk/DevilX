#pragma once
#include "Socket.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CNetworkAcceptor
			:public TBaseObject<CNetworkAcceptor>
		{
		protected:
			CSocket mSocketV4;
			CSocket mSocketV6;
			asio::ip::tcp::acceptor mInternalV4;
			asio::ip::tcp::acceptor mInternalV6;
		public:
			CNetworkAcceptor(unsigned short port);
			~CNetworkAcceptor();
		protected:
			static void _acceptHandler(const asio::error_code& error);
		};
	}
}