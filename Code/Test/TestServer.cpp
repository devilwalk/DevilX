// Project.cpp : Defines the entry point for the console application.
//

#include "Common.h"
#include "NetworkSystem/INetworkSystemInterface.h"
using namespace NSDevilX;
class CSystemListener
	:public NSNetworkSystem::ISystemListener
{
	// ͨ�� ISystemListener �̳�
	virtual Boolean onSearch(String destIP,UInt16 port) override
	{
		return true;
	}

	// ͨ�� ISystemListener �̳�
	virtual Void onSearched(NSNetworkSystem::ILink * link) override
	{
	}
};
class CServerListener
	:public NSNetworkSystem::IServerListener
{
	// ͨ�� IServerListener �̳�
	virtual Boolean onConnect(String clientIP,UInt16 clientPort) override
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
	NSNetworkSystem::getSystem()->searchServer("127.0.0.1");
	//auto client=NSNetworkSystem::getSystem()->createClient("127.0.0.1",server->getPort());
	//client->getLink()->addSendData("fuck",strlen("fuck"));
	while(true)
		NSNetworkSystem::getSystem()->update();
	NSNetworkSystem::getSystem()->shutdown();
	return 0;
}

