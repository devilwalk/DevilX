#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkAcceptor::CNetworkAcceptor(UInt16 port)
	:mInternalV4(CNetworkManager::getSingleton().getIOContext(),asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
	,mInternalV6(CNetworkManager::getSingleton().getIOContext(),asio::ip::tcp::endpoint(asio::ip::tcp::v6(),port))
{
}

NSDevilX::NSCore::CNetworkAcceptor::~CNetworkAcceptor()
{
}

NSDevilX::Void NSDevilX::NSCore::CNetworkAcceptor::_acceptV4()
{
	std::shared_ptr<asio::ip::tcp::socket> s(new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOContext()));
	mInternalV4.async_accept(*s,[s,this](const asio::error_code& error)
	{
		if(!error)
		{
			mConnectedSockets.push_back(s);
		}
		_acceptV4();
	}
	);
}

NSDevilX::Void NSDevilX::NSCore::CNetworkAcceptor::_acceptV6()
{
	std::shared_ptr<asio::ip::tcp::socket> s(new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOContext()));
	mInternalV6.async_accept(*s,[s,this](const asio::error_code& error)
	{
		if(!error)
		{
			mConnectedSockets.push_back(s);
		}
		_acceptV6();
	}
	);
}