#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::IServerImp::IServerImp(UInt16 port)
	:mPort(port)
	,mListener(nullptr)
{}

NSDevilX::NSNetworkSystem::IServerImp::~IServerImp()
{}

UInt16 NSDevilX::NSNetworkSystem::IServerImp::getPort() const
{
	return mPort;
}

Void NSDevilX::NSNetworkSystem::IServerImp::setListener(IServerListener * listener)
{
	mListener=listener;
}

IServerListener * NSDevilX::NSNetworkSystem::IServerImp::getListener() const
{
	return mListener;
}
