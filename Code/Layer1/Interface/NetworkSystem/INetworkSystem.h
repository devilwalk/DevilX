#pragma once
#include "INetworkServer.h"
#include "INetworkClient.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ISystemListener
		{
		protected:
			virtual ~ISystemListener(){}
		public:
			virtual Boolean onSearch(String destIP,UInt16 port)=0;
			virtual Void onSearched(ILink * link)=0;
		};
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void shutdown()=0;
			virtual Void update()=0;
			virtual Void searchServer(const String & serverIP,UInt16 serverPortStart=1024,UInt16 serverPortEnd=-1)=0;
			virtual IServer * createServer(UInt16 port=-1)=0;
			virtual IServer * getServer(UInt16 port)const=0;
			virtual Void destroyServer(IServer * server)=0;
			virtual IClient * createClient(const String & destIP,UInt16 port)=0;
			virtual IClient * getClient(const String & destIP,UInt16 port)const=0;
			virtual Void destroyClient(IClient * client)=0;
			virtual Void setListener(ISystemListener * listener)=0;
			virtual ISystemListener * getListener()const=0;
		};
		ISystem * getSystem();
	}
}