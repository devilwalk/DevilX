#pragma once
#include "INetworkHostImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CNetworkManager
			:public TSingleton<CNetworkManager>
			,public TBaseObject<CNetworkManager>
		{
		public:
		protected:
			asio::io_context mIOContext;
			TVector<String> mHostIPs;
			TNamedResourcePtrMap(INetworkHostImp) mHosts;
			TResourcePtrSet(INetworkConnectionImp) mConnections;
		public:
			CNetworkManager();
			~CNetworkManager();

			asio::io_context & getIOContext()
			{
				return mIOContext;
			}
			const TVector<String> & getHostIPs()const
			{
				return mHostIPs;
			}
			INetworkHostImp * createOrRetrieveHost(const String & ip);
			INetworkConnectionImp * createConnection(INetworkHostImp * host,asio::ip::tcp::socket * s);
			template<typename TCallback>
			Void createConnection(const String & endPointIP,UInt16 endPointPort,INetworkHostImp * host,UInt16 hostPort,TCallback callback)
			{
				auto s=DEVILX_TYPED_ALLOC(asio::ip::tcp::socket,1);
				s->asio::basic_stream_socket<asio::ip::tcp>::basic_stream_socket(CNetworkManager::getSingleton().getIOContext(),asio::ip::tcp::endpoint(asio::ip::make_address(host->getIP()),hostPort));
				asio::ip::tcp::endpoint remote_end_point(asio::ip::make_address(endPointIP.c_str()),endPointPort);
				s->async_connect(remote_end_point,[host,s,callback,this](const asio::error_code& error)
				{
					if(!error)
					{
						callback(createConnection(host,s));
					}
					else
					{
						DEVILX_OBJECT_DELETE(s);
#ifdef _MSC_VER
						OutputDebugStringA(("\r\nCNetworkManager::createConnection:"+error.message()+"\r\n").c_str());
#endif
					}
				});
			}
			Void destroyConnection(INetworkConnectionImp * connection);
		};
	}
}