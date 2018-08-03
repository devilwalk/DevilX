#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

std::vector<std::string> NSDevilX::NSCore::INetworkManager::getHostIPs() const
{
	std::vector<std::string> ret;
	asio::ip::tcp::resolver r(CNetworkManager::getSingleton().getIOContext());
	auto iter=r.resolve(asio::ip::host_name(),"");
	const asio::ip::tcp::resolver::iterator end;
	while(iter!=end)
	{
		asio::ip::tcp::endpoint endpoint=*iter++;
		ret.push_back(endpoint.address().to_string());
	}
	return ret;
}

INetworkHost * NSDevilX::NSCore::INetworkManager::createOrRetrieveHost(const std::string & ip)
{
	return CNetworkManager::getSingleton().createOrRetrieveHost(String(ip.begin(),ip.end()));
}

void NSDevilX::NSCore::INetworkManager::destroyConnection(INetworkConnection * connection)
{
	CNetworkManager::getSingleton().destroyConnection(static_cast<INetworkConnectionImp*>(connection));
}