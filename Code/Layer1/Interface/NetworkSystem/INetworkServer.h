#pragma once
#include "INetworkLink.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IServerListener
		{
		protected:
			virtual ~IServerListener()
			{}
		public:
			virtual Boolean onConnect(String destIP,UInt16 port,TVector<Byte> connectData)=0;
			virtual Void onDeconnect(ILink * link)=0;
		};
		class IServer
		{
		protected:
			virtual ~IServer(){}
		public:
			virtual UInt16 getPort()const=0;
			virtual Void setListener(IServerListener * listener)=0;
			virtual IServerListener * getListener()const=0;
		};
	}
}