#pragma once
#include "NetworkAcceptor.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CNetworkManager
			:public TSingletonEx<CNetworkManager>
			,public TBaseObject<CNetworkManager>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_UnprocessedConnection
			};
		protected:
			asio::io_context mIOContext;
			TNamedResourcePtrMap<CNetworkAcceptor> mAcceptors;
			TResourcePtrList<INetworkConnectionImp> mUnprocessedConnections;
			INetworkConnectionImp * mCurrentNotifyUnprocessedConnection;
		public:
			CNetworkManager();
			~CNetworkManager();

			asio::io_context & getIOContext()
			{
				return mIOContext;
			}
			Void update();
			static String makeAcceptKey(UInt16 localPort,const String & localIP="")
			{
				return localIP+":"+CStringUtility::toString(localPort);
			}
			CNetworkAcceptor * createAcceptor(UInt16 localPort,const String & localIP="");
			CNetworkAcceptor * getAcceptor(UInt16 localPort,const String & localIP="")const{ return mAcceptors.get(makeAcceptKey(localPort,localIP)); }
			Void destroyAcceptor(CNetworkAcceptor * acceptor);
			Void createConnection(const std::string & endPointIP,UInt16 endPointPort,UInt16 localPort,const std::string & localIP);
			Void destroyConnection(INetworkConnectionImp * connection);
		};
	}
}