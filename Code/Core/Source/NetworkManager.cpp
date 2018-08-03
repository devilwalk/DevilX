#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkManager::CNetworkManager()
{
	mIOContext.run();
}

NSDevilX::NSCore::CNetworkManager::~CNetworkManager()
{
	mHosts.destroyAll();
}

INetworkHostImp * NSDevilX::NSCore::CNetworkManager::createOrRetrieveHost(const String & ip)
{
	INetworkHostImp * ret=mHosts.get(ip);
	if(!ret)
	{
		ret=new INetworkHostImp(ip);
		mHosts.add(ip,ret);
	}
	return ret;
}

INetworkConnectionImp * NSDevilX::NSCore::CNetworkManager::createConnection(asio::ip::tcp::socket * s)
{
	auto connection = new INetworkConnectionImp(s);
	mConnections.insert(connection);
	return connection;
}

Void NSDevilX::NSCore::CNetworkManager::destroyConnection(INetworkConnectionImp * connection)
{
	mConnections.destroy(connection);
}
