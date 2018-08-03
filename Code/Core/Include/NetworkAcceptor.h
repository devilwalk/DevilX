#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CNetworkAcceptor
			:public TBaseObject<CNetworkAcceptor>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_NewConnection
			};
		protected:
			asio::ip::tcp::acceptor mInternal;
		public:
			CNetworkAcceptor(const String & ip,UInt16 port);
			~CNetworkAcceptor();
			UInt16 getPort()const{ return mInternal.local_endpoint().port(); }
			Void start();
		protected:
			Void _accept();
		};
	}
}