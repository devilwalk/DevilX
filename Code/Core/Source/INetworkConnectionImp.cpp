#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::INetworkConnectionImp::INetworkConnectionImp(asio::ip::tcp::socket * s)
	:mSocket(s)
{
}

NSDevilX::NSCore::INetworkConnectionImp::~INetworkConnectionImp()
{
	delete mSocket;
}

std::string NSDevilX::NSCore::INetworkConnectionImp::getMyIP() const
{
	// TODO: 在此处插入 return 语句
	return mSocket->local_endpoint().address().to_string();
}

unsigned short NSDevilX::NSCore::INetworkConnectionImp::getMyPort() const
{
	return mSocket->local_endpoint().port();
}

std::string NSDevilX::NSCore::INetworkConnectionImp::getEndPointIP() const
{
	// TODO: 在此处插入 return 语句
	return mSocket->remote_endpoint().address().to_string();
}

unsigned short NSDevilX::NSCore::INetworkConnectionImp::getEndPointPort() const
{
	return mSocket->remote_endpoint().port();
}

void NSDevilX::NSCore::INetworkConnectionImp::send(const void * data,size_t sizeInBytes)
{
	struct SCallback
	{
		TVector<Byte> mBuffer;
		SCallback(INetworkConnectionImp * connection,const void * data,size_t sizeInBytes)
		{
			mBuffer.resize(sizeInBytes);
			memcpy(&mBuffer[0],data,sizeInBytes);
		}
		void operator()(const asio::error_code& ec,std::size_t bytes_transferred)
		{
			delete this;
		}
	};
	auto callback=new SCallback(this,data,sizeInBytes);
	asio::async_write(*mSocket,asio::buffer(&callback->mBuffer[0],sizeInBytes),*callback);
}

void NSDevilX::NSCore::INetworkConnectionImp::addListener(IINetworkConnectionListener * listener)
{
}

void NSDevilX::NSCore::INetworkConnectionImp::removeListener(IINetworkConnectionListener * listener)
{
}
