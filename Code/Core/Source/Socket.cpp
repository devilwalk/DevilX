#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CSocket::CSocket()
	:mInternalTCP(CNetworkManager::getSingleton().getIOService())
	,mInternalUDP(CNetworkManager::getSingleton().getIOService())
{

}

NSDevilX::NSCore::CSocket::~CSocket()
{

}
