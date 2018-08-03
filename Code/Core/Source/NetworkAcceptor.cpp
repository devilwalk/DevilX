#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkAcceptor::CNetworkAcceptor(const String & ip,UInt16 port)
	:mInternal(CNetworkManager::getSingleton().getIOContext(),asio::ip::tcp::endpoint(asio::ip::make_address(ip.c_str()),port))
{
}

NSDevilX::NSCore::CNetworkAcceptor::~CNetworkAcceptor()
{
}

Void NSDevilX::NSCore::CNetworkAcceptor::start()
{
	_accept();
}

NSDevilX::Void NSDevilX::NSCore::CNetworkAcceptor::_accept()
{
	std::auto_ptr<asio::ip::tcp::socket> s(new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOContext()));
	mInternal.async_accept(*s,[&](const asio::error_code& error)
	{
		if(!error)
		{
			notify(EMessage_NewConnection,&s);
		}
		_accept();
	}
	);
}