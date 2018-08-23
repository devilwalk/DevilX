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

ConstCharPtr NSDevilX::NSCore::INetworkHostImp::getIP() const
{
	return mIP.c_str();
}

Void NSDevilX::NSCore::INetworkHostImp::addListeningPort(UInt16 port)
{
	if(!mAcceptors.has(port))
	{
		auto acceptor=DEVILX_NEW CNetworkAcceptor(mIP,port);
		mAcceptors.add(port,acceptor);
		acceptor->addListener(static_cast<TMessageReceiver<CNetworkAcceptor>*>(this),CNetworkAcceptor::EMessage_NewConnection);
		acceptor->start();
	}
}

Void NSDevilX::NSCore::INetworkHostImp::removeListeningPort(UInt16 port)
{
	mAcceptors.destroy(port);
}

Void NSDevilX::NSCore::INetworkHostImp::createOrRetrieveConnection(ConstCharPtr endPointIP, UInt16 endPointPort, UInt16 hostPort)
{
	CNetworkManager::getSingleton().createConnection(endPointIP,endPointPort,this,hostPort,[this](INetworkConnectionImp * connection)
	{
		connection->addListener(static_cast<TMessageReceiver<INetworkConnectionImp>*>(this),INetworkConnectionImp::EMessage_BeginDestruction);
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
		auto s=static_cast<asio::ip::tcp::socket*>(data);
		auto connection=CNetworkManager::getSingleton().createConnection(this,s);
		connection->addListener(static_cast<TMessageReceiver<INetworkConnectionImp>*>(this),INetworkConnectionImp::EMessage_BeginDestruction);
		mConnections.push_back(connection);
	}
	break;
	default:
		break;
	}
}

Void NSDevilX::NSCore::INetworkHostImp::onMessage(INetworkConnectionImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case INetworkConnectionImp::EMessage_BeginDestruction:
		mConnections.remove(notifier);
		break;
	}
}
