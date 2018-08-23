#pragma once
#include "INetworkPeer.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ISystemListener
		{
		protected:
			virtual ~ISystemListener(){}
		public:
			virtual Void onSearched(ILink * link)=0;
		};
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void shutdown()=0;
			virtual Void update()=0;
			virtual Void searchPeer(const String & key,const String & remoteIP,UInt16 remotePortStart=1024,UInt16 remotePortEnd=-1)=0;
			virtual IPeer * createPeer(const String & localIP,UInt16 localPort)=0;
			virtual IPeer * getPeer(const String & localIP,UInt16 localPort)const=0;
			virtual Void destroyPeer(IPeer * peer)=0;
			virtual ILink * createLink(const String & remoteIP,UInt16 remotePort,const String & localIP="",UInt16 localPort=0)=0;
			virtual ILink * getLink(const String & remoteIP,UInt16 remotePort,const String & localIP="",UInt16 localPort=0)const=0;
			virtual Void destroyLink(ILink * link)=0;
			virtual Void setListener(ISystemListener * listener)=0;
			virtual ISystemListener * getListener()const=0;
		};
		ISystem * getSystem();
	}
}