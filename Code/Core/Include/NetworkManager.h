#pragma once
#include "INetworkHostImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CNetworkManager
			:public TSingletonEx<CNetworkManager>
			,public TBaseObject<CNetworkManager>
		{
		public:
		protected:
			asio::io_context mIOContext;
			TNamedResourcePtrMap(INetworkHostImp) mHosts;
			TResourcePtrSet(INetworkConnectionImp) mConnections;
		public:
			CNetworkManager();
			~CNetworkManager();

			asio::io_context & getIOContext()
			{
				return mIOContext;
			}
			INetworkHostImp * createOrRetrieveHost(const String & ip);
			INetworkConnectionImp * createConnection(asio::ip::tcp::socket * s);
			template<typename TCallback>
			Void createConnection(const String & endPointIP,UInt16 endPointPort,const String & hostIP,UInt16 hostPort,TCallback callback)
			{
				std::auto_ptr<asio::ip::tcp::socket> s(new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOContext(),asio::ip::tcp::endpoint(asio::ip::make_address(hostIP.c_str()),hostPort)));
				asio::ip::tcp::endpoint remote_end_point(asio::ip::make_address(endPointIP.c_str()),endPointPort);
				s->async_connect(remote_end_point,[&s,callback,this](const asio::error_code& error)
				{
					if(!error)
					{
						callback(createConnection(s.release()));
					}
				});
			}
			Void destroyConnection(INetworkConnectionImp * connection);
		};
	}
}