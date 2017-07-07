#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::IClientImp::IClientImp(const String & serverIP,UInt16 port)
	:mLink(nullptr)
{
	mLink=ISystemImp::getSingleton().createLink(serverIP,port,"127.0.0.1",-1);
}

NSDevilX::NSNetworkSystem::IClientImp::~IClientImp()
{
	if(ISystemImp::getSingleton().isExit())
		return;
	ISystemImp::getSingleton().destroyLink(mLink);
}

ILink * NSDevilX::NSNetworkSystem::IClientImp::getLink() const
{
	return mLink;
}