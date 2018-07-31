#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::INetworkConnection * NSDevilX::NSCore::INetworkManager::createConnection(const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort /*= -1*/,const std::string & localIP /*=std::string("")*/)
{
	return nullptr;
}

void NSDevilX::NSCore::INetworkManager::sendTo(const void * data,size_t sizeInBytes,const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort/*=-1*/,const std::string & localIP/*=std::string("")*/)
{

}

void NSDevilX::NSCore::INetworkManager::addListener(INetworkManagerListener * listener)
{

}

void NSDevilX::NSCore::INetworkManager::removeListener(INetworkManagerListener * listener)
{

}
