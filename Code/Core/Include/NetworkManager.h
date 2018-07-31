#pragma once
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
		public:
			CNetworkManager();
			~CNetworkManager();

			asio::io_context & getIOService()
			{
				return mIOService;
			}
		};
	}
}