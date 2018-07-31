#pragma once
#include "ICoreNetworkConnection.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkManagerListener
		{
		protected:
			virtual ~INetworkManagerListener(){}
		public:
			virtual void onConnectionComeIn(INetworkConnection * connect)=0;
			virtual void onUnConnectedDataReceived(const void * data,size_t sizeInBytes)=0;
		};
		class DLLAPI INetworkManager
		{
		protected:
			~INetworkManager(){}
		public:
			virtual INetworkConnection * createConnection(const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort = -1,const std::string & localIP =std::string(""));
			virtual void sendTo(const void * data,size_t sizeInBytes,const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort=-1,const std::string & localIP=std::string(""));
			virtual void addListener(INetworkManagerListener * listener);
			virtual void removeListener(INetworkManagerListener * listener);
		};
	}
}