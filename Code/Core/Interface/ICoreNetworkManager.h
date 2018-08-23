#pragma once
#include "ICoreNetworkHost.h"
#include "ICoreNetworkConnection.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI INetworkManager
		{
		protected:
			~INetworkManager(){}
		public:
			SizeT getNumHostIPs()const;
			ConstCharPtr getHostIP(SizeT index)const;
			INetworkHost * createOrRetrieveHost(ConstCharPtr ip);
			Void destroyConnection(INetworkConnection * connection);
			Void update();
		};
	}
}