// Project.cpp : Defines the entry point for the console application.
//

#include "Common.h"
#include "NetworkSystem/INetworkSystemInterface.h"
using namespace NSDevilX;
class CSystemListener
	:public NSNetworkSystem::ISystemListener
{
	// 通过 ISystemListener 继承
	virtual Void onSearch(String destIP,UInt16 port,ConstVoidPtr connectData,UInt32 connectDataSizeInBytes) override
	{
		return Void();
	}
};
class CServerListener
	:public NSNetworkSystem::IServerListener
{
	// 通过 IServerListener 继承
	virtual Boolean onConnect(String clientIP,UInt16 clientPort,ConstVoidPtr connectData,UInt32 connectDataSizeInBytes) override
	{
		return true;
	}
	virtual Void onConnected(NSNetworkSystem::ILink * link) override
	{
	}
	virtual Void onDeconnect(NSNetworkSystem::ILink * link) override
	{
		return Void();
	}
};
int main()
{
	CSystemListener system_listener;
	CServerListener server_listener;
	NSNetworkSystem::getSystem()->setListener(&system_listener);
	auto server=NSNetworkSystem::getSystem()->createServer();
	server->setListener(&server_listener);
	NSNetworkSystem::getSystem()->searchServer("127.0.0.1","search",strlen("search"));
	auto client=NSNetworkSystem::getSystem()->createClient("127.0.0.1",server->getPort());
	client->getLink()->pushSendData("fuck",strlen("fuck"));
	while(true)
		NSNetworkSystem::getSystem()->update();
	NSNetworkSystem::getSystem()->shutdown();
	return 0;
}

