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

Void NSDevilX::NSNetworkSystem::ISystemImp::searchServer(const String & serverIP,const TVector<Byte> & connectData,UInt16 serverPortStart=49152,UInt16 serverPortEnd=-1)
{
	struct SSearch
	{
		const String & mServerIP;
		const TVector<Byte> & mConnectData;
		UInt16 mServerPortStart;
		UInt16 mServerPortEnd;
	};
	SSearch s={serverIP,connectData,serverPortStart,serverPortEnd};
	notify(EMessage_SearchServer,&s);
}

IServer * NSDevilX::NSNetworkSystem::ISystemImp::createServer(UInt16 port)
{
	IServerImp * ret=mServers.get(port);
	if(ret)
		return nullptr;
	notify(EMessage_BeginCreateServer);
	ret=DEVILX_NEW IServerImp(port);
	mServers.add(port,ret);
	notify(EMessage_EndCreateServer,ret);
	return ret;
}

IServer * NSDevilX::NSNetworkSystem::ISystemImp::getServer(UInt16 port) const
{
	return mServers.get(port);
}

Void NSDevilX::NSNetworkSystem::ISystemImp::destroyServer(IServer * server)
{
	notify(EMessage_BeginDestroyServer);
	mServers.destroy(server->getPort());
	notify(EMessage_EndDestroyServer);
}

IClient * NSDevilX::NSNetworkSystem::ISystemImp::createClient(const String & destIP,UInt16 port)
{
	const String key=destIP+":"+CStringConverter::toString(port);
	IClientImp * ret=mClients.get(key);
	if(ret)
		return nullptr;
	notify(EMessage_BeginCreateClient);
	ret=DEVILX_NEW IClientImp(destIP,port);
	mClients.add(key,ret);
	notify(EMessage_EndCreateClient);
	return ret;
}

IClient * NSDevilX::NSNetworkSystem::ISystemImp::getClient(const String & destIP,UInt16 port) const
{
	const String key=destIP+":"+CStringConverter::toString(port);
	return mClients.get(key);
}

Void NSDevilX::NSNetworkSystem::ISystemImp::destroyClient(IClient * client)
{
	const String key=client->getLink()->getServerIP()+":"+CStringConverter::toString(client->getLink()->getServerPort());
	notify(EMessage_BeginDestroyClient);
	mClients.destroy(key);
	notify(EMessage_EndDestroyClient);
}

Void NSDevilX::NSNetworkSystem::ISystemImp::setListener(ISystemListener * listener)
{
	mListener=listener;
}

ISystemListener * NSDevilX::NSNetworkSystem::ISystemImp::getListener() const
{
	return mListener;
}
