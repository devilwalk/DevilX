#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
NSDevilX::NSNetworkSystem::ISystemImp::ISystemImp()
	:mExit(False)
{}

NSDevilX::NSNetworkSystem::ISystemImp::~ISystemImp()
{
	mExit=True;
	notify(EMessage_Destruction);
}

Void NSDevilX::NSNetworkSystem::ISystemImp::shutdown()
{
	DEVILX_DELETE(this);
}

Void NSDevilX::NSNetworkSystem::ISystemImp::update()
{
	notify(EMessage_Update);
}

ILink * NSDevilX::NSNetworkSystem::ISystemImp::createLink(const String & name,const String & destIP)
{
	if(mLinks.has(name))
		return nullptr;
	notify(EMessage_BeginCreateLink);
	auto * ret=DEVILX_NEW ILinkImp(name,destIP);
	mLinks[name]=ret;
	notify(EMessage_EndCreateLink,ret);
	return ret;
}

ILink * NSDevilX::NSNetworkSystem::ISystemImp::popUnprocessedLink(const String & name)
{
	notify(EMessage_PopUnprocessedLink);
	return getLink(name);
}

ILink * NSDevilX::NSNetworkSystem::ISystemImp::getLink(const String & name) const
{
	return mLinks.has(name)?mLinks.get(name):nullptr;
}

Void NSDevilX::NSNetworkSystem::ISystemImp::destroyLink(ILink * link)
{
	if(!mLinks.has(link->getName()))
		return;
	notify(EMessage_BeginDestroyLink,static_cast<ILinkImp*>(link));
	mLinks.destroy(link->getName());
	notify(EMessage_EndDestroyLink);
}
