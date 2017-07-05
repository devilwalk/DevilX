#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::IServerImp::IServerImp(UInt16 port)
	:mPort(port)
	,mListener(nullptr)
{}

NSDevilX::NSNetworkSystem::IServerImp::~IServerImp()
{}

Void NSDevilX::NSNetworkSystem::IServerImp::addLink(ILinkImp * link)
{
	mLinks.push_back(link);
}

UInt16 NSDevilX::NSNetworkSystem::IServerImp::getPort() const
{
	return mPort;
}

Void NSDevilX::NSNetworkSystem::IServerImp::close(ILink * link)
{
	if(mLinks.remove(static_cast<ILinkImp*>(link)))
	{
		ISystemImp::getSingleton().destroyLink(static_cast<ILinkImp*>(link));
	}
}

Void NSDevilX::NSNetworkSystem::IServerImp::setListener(IServerListener * listener)
{
	mListener=listener;
}

IServerListener * NSDevilX::NSNetworkSystem::IServerImp::getListener() const
{
	return mListener;
}
