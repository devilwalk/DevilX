#pragma once
#include "ICoreNetworkConnection.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkHost
		{
		protected:
			virtual ~INetworkHost(){}
		public:
			virtual ConstCharPtr getIP()const=0;
			virtual Void addListeningPort(UInt16 port)=0;
			virtual Void removeListeningPort(UInt16 port)=0;
			virtual Void createOrRetrieveConnection(ConstCharPtr endPointIP,UInt16 endPointPort,UInt16 hostPort=0)=0;
			virtual SizeT getNumConnections()const=0;
			virtual INetworkConnection * getConnection(SizeT index)const=0;
		};
	}
}