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
			std::vector<std::string> getHostIPs()const;
			INetworkHost * createOrRetrieveHost(const std::string & ip);
			Void destroyConnection(INetworkConnection * connection);
		};
	}
}