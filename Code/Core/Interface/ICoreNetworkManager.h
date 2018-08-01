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
			virtual void onNewConnection(INetworkConnection * connect)=0;
			virtual void onUnConnectedDataReceived(const void * data,size_t sizeInBytes)=0;
		};
		class DLLAPI INetworkManager
		{
		protected:
			~INetworkManager(){}
		public:
			void createConnection(const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort=-1,const std::string & localIP=std::string(""));
			void destroyConnection(INetworkConnection * connection);
			void addListeningPort(unsigned short port);
			void removeListeningPort(unsigned short port);
			void sendTo(const void * data,size_t sizeInBytes,const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort=-1,const std::string & localIP=std::string(""));
			void addListener(INetworkManagerListener * listener);
			void removeListener(INetworkManagerListener * listener);
		};
	}
}