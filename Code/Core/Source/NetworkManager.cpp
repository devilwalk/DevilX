#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkManager::CNetworkManager()
{

}

NSDevilX::NSCore::CNetworkManager::~CNetworkManager()
{

}

NSDevilX::NSCore::CNetworkAcceptor * NSDevilX::NSCore::CNetworkManager::createAcceptor(UInt16 port)
{
	assert(nullptr==getAcceptor(port));
	auto ret=new CNetworkAcceptor(port);
	mAcceptors.add(port,ret);
	return ret;
}

NSDevilX::NSCore::Void NSDevilX::NSCore::CNetworkManager::removeListeningPort(CNetworkAcceptor * acceptor)
{
	mAcceptors.destroy(acceptor->getPort());
}
