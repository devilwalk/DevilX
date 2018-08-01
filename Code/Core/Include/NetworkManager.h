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
			TResourcePtrMap<UInt16,CNetworkAcceptor> mAcceptors;
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
			CNetworkAcceptor * createAcceptor(UInt16 port);
			CNetworkAcceptor * getAcceptor(UInt16 port)const{ return mAcceptors.get(port); }
			Void destroyAcceptor(CNetworkAcceptor * acceptor);
			Void createConnection(const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort,const std::string & localIP);
			Void destroyConnection(INetworkConnectionImp * connection);
		};
	}
}