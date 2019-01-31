#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkManager::CNetworkManager()
{
	asio::ip::tcp::resolver r(mIOContext);
	auto iter=r.resolve(asio::ip::host_name(),"");
	const asio::ip::tcp::resolver::iterator end;
	while(iter!=end)
	{
		asio::ip::tcp::endpoint endpoint=*iter++;
		auto str=endpoint.address().to_string();
		mHostIPs.push_back(String(str.begin(),str.end()));
	}
}

NSDevilX::NSCore::CNetworkManager::~CNetworkManager()
{
	mConnections.destroyAll();
	mHosts.destroyAll();
}

INetworkHostImp * NSDevilX::NSCore::CNetworkManager::createOrRetrieveHost(const String & ip)
{
	INetworkHostImp * ret=mHosts.get(ip);
	if(!ret)
	{
		ret=DEVILX_NEW INetworkHostImp(ip);
		mHosts.add(ip,ret);
	}
	return ret;
}

INetworkConnectionImp * NSDevilX::NSCore::CNetworkManager::createConnection(INetworkHostImp * host,asio::ip::tcp::socket * s)
{
	auto connection =DEVILX_NEW INetworkConnectionImp(host,s);
	mConnections.insert(connection);
	return connection;
}

Void NSDevilX::NSCore::CNetworkManager::destroyConnection(INetworkConnectionImp * connection)
{
	mConnections.destroy(connection);
}
