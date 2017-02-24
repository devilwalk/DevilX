#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
NSDevilX::NSNetworkSystem::ISystemImp::ISystemImp()
	:mExit(False)
	,mListener(nullptr)
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

Void NSDevilX::NSNetworkSystem::ISystemImp::search(const String & destIP,UInt16 portStart,UInt16 portEnd)
{
	struct SSearch
	{
		const String & mDestIP;
		UInt16 mPortStart;
		UInt16 mPortEnd;
	};
	SSearch s={destIP,portStart,portEnd};
	notify(EMessage_Search,&s);
}

ILink * NSDevilX::NSNetworkSystem::ISystemImp::createLink(const String & destIP,UInt16 port)
{
	auto key=destIP+":"+CStringConverter::toString(port);
	if(mLinks.has(key))
		return nullptr;
	notify(EMessage_BeginCreateLink);
	auto * ret=DEVILX_NEW ILinkImp(destIP,port);
	mLinks[key]=ret;
	notify(EMessage_EndCreateLink,ret);
	return ret;
}

ILink * NSDevilX::NSNetworkSystem::ISystemImp::getLink(const String & destIP,UInt16 port) const
{
	auto key=destIP+":"+CStringConverter::toString(port);
	return mLinks.has(key)?mLinks.get(key):nullptr;
}

Void NSDevilX::NSNetworkSystem::ISystemImp::destroyLink(ILink * link)
{
	auto key=link->getDestination()+":"+CStringConverter::toString(link->getPort());
	if(!mLinks.has(key))
		return;
	notify(EMessage_BeginDestroyLink,static_cast<ILinkImp*>(link));
	mLinks.destroy(key);
	notify(EMessage_EndDestroyLink);
}

Void NSDevilX::NSNetworkSystem::ISystemImp::setListener(ISystemListener * listener)
{
	mListener=listener;
}

ISystemListener * NSDevilX::NSNetworkSystem::ISystemImp::getListener() const
{
	return mListener;
}
