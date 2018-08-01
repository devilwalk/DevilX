#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkConnectionImp
			:public INetworkConnection
			,public TBaseObject<INetworkConnectionImp>
		{
		protected:
			std::shared_ptr<asio::ip::tcp::socket> mSocket;
		public:
			INetworkConnectionImp(std::shared_ptr<asio::ip::tcp::socket> s);
			~INetworkConnectionImp();

			// Í¨¹ý INetworkConnection ¼Ì³Ð
			virtual std::string getMyIP() const override;
			virtual unsigned short getMyPort() const override;
			virtual std::string getEndPointIP() const override;
			virtual unsigned short getEndPointPort() const override;
			virtual void send(const void * data,size_t sizeInBytes) override;
			virtual void addListener(IINetworkConnectionListener * listener) override;
			virtual void removeListener(IINetworkConnectionListener * listener) override;
		};
	}
}