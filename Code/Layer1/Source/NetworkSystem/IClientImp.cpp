#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::IClientImp::IClientImp(ILinkImp * link)
	:mLink(link)
{}

NSDevilX::NSNetworkSystem::IClientImp::~IClientImp()
{
	ISystemImp::getSingleton().destroyLink(getLink());
}
