#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::IClientImp::IClientImp(const String & serverIP,UInt16 port)
	:mLink(nullptr)
{
	mLink=DEVILX_NEW ILinkImp(serverIP,port,"127.0.0.1",-1);
}

NSDevilX::NSNetworkSystem::IClientImp::~IClientImp()
{
	DEVILX_DELETE(mLink);
}

ILink * NSDevilX::NSNetworkSystem::IClientImp::getLink() const
{
	return mLink;
}
