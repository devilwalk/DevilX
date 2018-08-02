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
			virtual void onUnConnectedDataReceived(ConstVoidPtr data,SizeT sizeInBytes)=0;
		};
		class DLLAPI INetworkManager
		{
		protected:
			~INetworkManager(){}
		public:
			void createConnection(const std::string & endPointIP,UInt16 endPointPort,UInt16 localPort=-1,const std::string & localIP=std::string(""));
			void destroyConnection(INetworkConnection * connection);
			void addListeningPort(UInt16 localPort,const std::string & localIP=std::string(""));
			void removeListeningPort(UInt16 localPort,const std::string & localIP=std::string(""));
			void sendTo(ConstVoidPtr data,SizeT sizeInBytes,const std::string & endPointIP,UInt16 endPointPort,UInt16 localPort=-1,const std::string & localIP=std::string(""));
			void addListener(INetworkManagerListener * listener);
			void removeListener(INetworkManagerListener * listener);
		};
	}
}