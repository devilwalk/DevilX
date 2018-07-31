#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CSocket
			:public TBaseObject<CSocket>
		{
		protected:
			asio::ip::tcp::socket mInternalTCP;
			asio::ip::udp::socket mInternalUDP;
		public:
			CSocket();
			~CSocket();

			decltype(mInternalTCP) & getTCPSocket()
			{
				return mInternalTCP;
			}
			decltype(mInternalUDP) & getUDPSocket()
			{
				return mInternalUDP;
			}
		};
	}
}