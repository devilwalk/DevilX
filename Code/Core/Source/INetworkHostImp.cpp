#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::INetworkHostImp::INetworkHostImp(const String & ip)
	:mIP(ip)
{

}

NSDevilX::NSCore::INetworkHostImp::~INetworkHostImp()
{

}

std::string NSDevilX::NSCore::INetworkHostImp::getIP() const
{
	return std::string(mIP.begin(),mIP.end());
}

Void NSDevilX::NSCore::INetworkHostImp::addListeningPort(UInt16 port)
{
	if(!mAcceptors.has(port))
	{
		auto acceptor=new CNetworkAcceptor(mIP,port);
		mAcceptors.add(port,acceptor);
		acceptor->addListener(this,CNetworkAcceptor::EMessage_NewConnection);
	}
}

Void NSDevilX::NSCore::INetworkHostImp::removeListeningPort(UInt16 port)
{
	mAcceptors.destroy(port);
}

Void NSDevilX::NSCore::INetworkHostImp::createOrRetrieveConnection(const std::string & endPointIP, UInt16 endPointPort, UInt16 hostPort)
{
	CNetworkManager::getSingleton().createConnection(endPointIP.c_str(),endPointPort,mIP,hostPort,[this](INetworkConnectionImp * connection)
	{
		mConnections.push_back(connection);
	});
}

SizeT NSDevilX::NSCore::INetworkHostImp::getNumConnections() const
{
	return mConnections.size();
}

INetworkConnection * NSDevilX::NSCore::INetworkHostImp::getConnection(SizeT index) const
{
	return mConnections[index];
}

NSDevilX::Void NSDevilX::NSCore::INetworkHostImp::onMessage(CNetworkAcceptor * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CNetworkAcceptor::EMessage_NewConnection:
	{
		auto s=static_cast<std::auto_ptr<asio::ip::tcp::socket>*>(data)->release();
		mConnections.push_back(CNetworkManager::getSingleton().createConnection(s));
	}
	break;
	default:
		break;
	}
}