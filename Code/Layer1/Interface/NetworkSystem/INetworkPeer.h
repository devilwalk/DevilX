#pragma once
#include "INetworkLink.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IPeer;
		class IPeerListener
		{
		protected:
			virtual ~IPeerListener()
			{}
		public:
			virtual Boolean onConnect(IPeer * peer,ILink * link)=0;
		};
		class IPeer
		{
		protected:
			virtual ~IPeer(){}
		public:
			virtual const String & getIP()const=0;
			virtual UInt16 getPort()const=0;
			virtual Void setConnectKey(const String & key)=0;
			virtual const String & getConnectKey()const=0;
			virtual Void setListener(IPeerListener * listener)=0;
			virtual IPeerListener * getListener()const=0;
		};
	}
}