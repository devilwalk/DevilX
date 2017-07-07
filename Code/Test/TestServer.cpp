// Project.cpp : Defines the entry point for the console application.
//

#include "Common.h"
#include "NetworkSystem/INetworkSystemInterface.h"
using namespace NSDevilX;
NSNetworkSystem::IServer * gServer=nullptr;
NSNetworkSystem::ILink * gServerLink=nullptr;
NSNetworkSystem::IClient * gClient=nullptr;
class CLinkListener
	:public NSNetworkSystem::ILinkListener
{
	// 通过 ILinkListener 继承
	virtual Void onDataReceived(NSNetworkSystem::ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes) override
	{
		if(link==gServerLink)
		{
			OutputDebugStringA("\r\n");
			OutputDebugStringA("Server Recv:");
			String text;
			text.resize(dataSizeInBytes+1);
			memcpy(&text[0],data,dataSizeInBytes);
			OutputDebugStringA(text.c_str());
			OutputDebugStringA("\r\n");
		}
		else
		{
			OutputDebugStringA("\r\n");
			OutputDebugStringA("Client Recv:");
			String text;
			text.resize(dataSizeInBytes+1);
			memcpy(&text[0],data,dataSizeInBytes);
			OutputDebugStringA(text.c_str());
			OutputDebugStringA("\r\n");
		}
	}
	virtual Void onDeconnect(NSNetworkSystem::ILink * link) override
	{
		return Void();
	}
};
CLinkListener gLinkListener;
class CSystemListener
	:public NSNetworkSystem::ISystemListener
{
	// 通过 ISystemListener 继承
	virtual Boolean onSearch(String destIP,UInt16 port) override
	{
		return gServer->getPort()==port;
	}

	// 通过 ISystemListener 继承
	virtual Void onSearched(NSNetworkSystem::ILink * link) override
	{
	}
};
class CServerListener
	:public NSNetworkSystem::IServerListener
{
	// 通过 IServerListener 继承
	virtual Boolean onConnect(NSNetworkSystem::IServer * server,const String & clientIP,UInt16 clientPort) override
	{
		return true;
	}
	virtual Void onConnected(NSNetworkSystem::IServer * server,NSNetworkSystem::ILink * link) override
	{
		assert(!gServerLink);
		gServerLink=link;
		gServerLink->setListener(&gLinkListener);
	}
};
int main()
{
	CSystemListener system_listener;
	CServerListener server_listener;
	NSNetworkSystem::getSystem()->setListener(&system_listener);
	gServer=NSNetworkSystem::getSystem()->createServer();
	gServer->setListener(&server_listener);
	//NSNetworkSystem::getSystem()->searchServer("127.0.0.1");
	gClient=NSNetworkSystem::getSystem()->createClient("127.0.0.1",gServer->getPort());
	gClient->getLink()->setListener(&gLinkListener);
	UInt32 number=0;
	while(number<10000)
	{
		String number_text=CStringConverter::toString(number);
		if(gServerLink)
			gServerLink->addSendData(&("Server Send:"+number_text)[0],static_cast<UInt32>(("Server Send:"+number_text).size()));
		gClient->getLink()->addSendData(&("Client Send:"+number_text)[0],static_cast<UInt32>(("Client Send:"+number_text).size()));
		NSNetworkSystem::getSystem()->update();
		number++;
	}
	NSNetworkSystem::getSystem()->shutdown();
	return 0;
}

