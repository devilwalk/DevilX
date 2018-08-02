#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

void NSDevilX::NSCore::INetworkManager::createConnection(const std::string & endPointIP,UInt16 endPointPort,UInt16 localPort,const std::string & localIP)
{
	CNetworkManager::getSingleton().createConnection(endPointIP,endPointPort,localPort,localIP);
}

void NSDevilX::NSCore::INetworkManager::destroyConnection(INetworkConnection * connection)
{
	CNetworkManager::getSingleton().destroyConnection(static_cast<INetworkConnectionImp*>(connection));
}

void NSDevilX::NSCore::INetworkManager::addListeningPort(UInt16 localPort,const std::string & localIP)
{
	if(!CNetworkManager::getSingleton().getAcceptor(port))
	{
		CNetworkManager::getSingleton().createAcceptor(port);
	}
}

void NSDevilX::NSCore::INetworkManager::removeListeningPort(UInt16 localPort,const std::string & localIP)
{
	auto acceptor=CNetworkManager::getSingleton().getAcceptor(port);
	if(acceptor)
		CNetworkManager::getSingleton().destroyAcceptor(acceptor);
}

void NSDevilX::NSCore::INetworkManager::sendTo(ConstVoidPtr data,SizeT sizeInBytes,const std::string & endPointIP,UInt16 endPointPort,UInt16 localPort,const std::string & localIP)
{
	asio::ip::udp::endpoint local_endpoint;
	if((static_cast<UInt16>(-1)!=localPort)&&(""!=localIP))
	{
		local_endpoint=asio::ip::udp::endpoint(asio::ip::make_address(localIP),localPort);
	}
	asio::ip::udp::socket s(CNetworkManager::getSingleton().getAcceptor,local_endpoint);
}

void NSDevilX::NSCore::INetworkManager::addListener(INetworkManagerListener * listener)
{
}

void NSDevilX::NSCore::INetworkManager::removeListener(INetworkManagerListener * listener)
{
}
