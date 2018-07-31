#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

INetworkConnection * NSDevilX::NSCore::INetworkManager::createConnection(const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort,const std::string & localIP)
{
	return nullptr;
}

void NSDevilX::NSCore::INetworkManager::destroyConnection(INetworkConnection * connection)
{
}

void NSDevilX::NSCore::INetworkManager::addListeningPort(unsigned short port)
{
}

void NSDevilX::NSCore::INetworkManager::removeListeningPort(unsigned short port)
{
}

void NSDevilX::NSCore::INetworkManager::sendTo(const void * data,size_t sizeInBytes,const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort,const std::string & localIP)
{
}

void NSDevilX::NSCore::INetworkManager::addListener(INetworkManagerListener * listener)
{
}

void NSDevilX::NSCore::INetworkManager::removeListener(INetworkManagerListener * listener)
{
}
