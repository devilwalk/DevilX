#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkAcceptor::CNetworkAcceptor(UInt16 port)
	:mInternalV4(CNetworkManager::getSingleton().getIOService(),asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
	,mInternalV6(CNetworkManager::getSingleton().getIOService(),asio::ip::tcp::endpoint(asio::ip::tcp::v6(),port))
{
}

NSDevilX::NSCore::CNetworkAcceptor::~CNetworkAcceptor()
{
}

NSDevilX::NSCore::Void NSDevilX::NSCore::CNetworkAcceptor::_acceptV4()
{
	std::shared_ptr<asio::ip::tcp::socket> s(new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOService()));
	mInternalV4.async_accept(*s,[this,s](const asio::error_code& error)
	{
		if(!error)
		{
			mConnectedSockets.push_back(s.get());
		}
		else
		{
		}
		_acceptV4();
	}
	);
}

NSDevilX::NSCore::Void NSDevilX::NSCore::CNetworkAcceptor::_acceptV6()
{
	std::shared_ptr<asio::ip::tcp::socket> s(new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOService()));
	mInternalV6.async_accept(*s,[this,s](const asio::error_code& error)
	{
		if(!error)
		{
		}
		else
		{
		}
		_acceptV6();
	}
	);
}