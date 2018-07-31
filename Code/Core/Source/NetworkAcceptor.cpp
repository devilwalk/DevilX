#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkAcceptor::CNetworkAcceptor(unsigned short port)
	:mInternalV4(CNetworkManager::getSingleton().getIOService(),asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
	,mInternalV6(CNetworkManager::getSingleton().getIOService(),asio::ip::tcp::endpoint(asio::ip::tcp::v6(),port))
{
	mInternalV4.async_accept(mSocketV4.getTCPSocket(),_acceptHandler);
	mInternalV6.async_accept(mSocketV6.getTCPSocket(),_acceptHandler);
}

NSDevilX::NSCore::CNetworkAcceptor::~CNetworkAcceptor()
{

}

void NSDevilX::NSCore::CNetworkAcceptor::_acceptHandler(const asio::error_code& error)
{

}
