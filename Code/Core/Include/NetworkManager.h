#pragma once
#include "NetworkAcceptor.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CNetworkManager
			:public TSingletonEx<CNetworkManager>
			,public TBaseObject<CNetworkManager>
		{
		protected:
			asio::io_context mIOService;
			TResourcePtrMap<UInt16,CNetworkAcceptor> mAcceptors;
		public:
			CNetworkManager();
			~CNetworkManager();

			asio::io_context & getIOService()
			{
				return mIOService;
			}
			CNetworkAcceptor * createAcceptor(UInt16 port);
			CNetworkAcceptor * getAcceptor(UInt16 port)const{ return mAcceptors.get(port); }
			Void removeListeningPort(CNetworkAcceptor * acceptor);
		};
	}
}