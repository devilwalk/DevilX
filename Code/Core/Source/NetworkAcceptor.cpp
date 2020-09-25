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
	auto s=new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOContext());
	mInternal.async_accept(*s,[s,this](const asio::error_code& error)
	{
		if(!error)
		{
			notify(EMessage_NewConnection,s);
		}
		else
		{
#ifdef _MSC_VER
			OutputDebugStringA(("\r\nCNetworkAcceptor::_accept:"+error.message()+"\r\n").c_str());
#endif
		}
		_accept();
	}
	);
}