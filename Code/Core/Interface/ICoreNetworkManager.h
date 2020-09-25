#pragma once
#include "ICoreNetworkHost.h"
#include "ICoreNetworkConnection.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI INetworkManager
		{
		public:
			~INetworkManager(){}
			SizeT getNumHostIPs()const;
			ConstCharPtr getHostIP(SizeT index)const;
			INetworkHost * createOrRetrieveHost(ConstCharPtr ip);
			Void destroyConnection(INetworkConnection * connection);
			Void update();
		};
	}
}