#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CSocket::CSocket()
	:mInternalTCP(CNetworkManager::getSingleton().getIOContext())
	,mInternalUDP(CNetworkManager::getSingleton().getIOContext())
{

}

NSDevilX::NSCore::CSocket::~CSocket()
{

}
