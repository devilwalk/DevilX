#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

SizeT NSDevilX::NSCore::INetworkManager::getNumHostIPs() const
{
	return CNetworkManager::getSingleton().getHostIPs().size();
}

ConstCharPtr NSDevilX::NSCore::INetworkManager::getHostIP(SizeT index) const
{
	return CNetworkManager::getSingleton().getHostIPs()[index].c_str();
}

INetworkHost * NSDevilX::NSCore::INetworkManager::createOrRetrieveHost(ConstCharPtr ip)
{
	return CNetworkManager::getSingleton().createOrRetrieveHost(ip);
}

void NSDevilX::NSCore::INetworkManager::destroyConnection(INetworkConnection * connection)
{
	CNetworkManager::getSingleton().destroyConnection(static_cast<INetworkConnectionImp*>(connection));
}

Void NSDevilX::NSCore::INetworkManager::update()
{
	CNetworkManager::getSingleton().getIOContext().poll();
}
