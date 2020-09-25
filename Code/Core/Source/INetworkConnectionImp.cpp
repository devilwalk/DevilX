#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::INetworkConnectionImp::INetworkConnectionImp(INetworkHostImp * host,asio::ip::tcp::socket * s)
	:mHost(host)
	,mSocket(s)
	,mValidate(True)
{
	mReceiveTemp.resize(4096);
	mSocket->async_read_some(asio::buffer(&mReceiveTemp[0],4096),std::bind(_read,this,std::placeholders::_1,std::placeholders::_2));
}

NSDevilX::NSCore::INetworkConnectionImp::~INetworkConnectionImp()
{
	notify(EMessage_BeginDestruction);
	DEVILX_DELETE(mSocket);
	notify(EMessage_EndDestruction);
}

Boolean NSDevilX::NSCore::INetworkConnectionImp::isValidate() const
{
	return mValidate;
}

INetworkHost * NSDevilX::NSCore::INetworkConnectionImp::getHost() const
{
	// TODO: 在此处插入 return 语句
	return mHost;
}

UInt16 NSDevilX::NSCore::INetworkConnectionImp::getHostPort() const
{
	return mSocket->local_endpoint().port();
}

ConstCharPtr NSDevilX::NSCore::INetworkConnectionImp::getEndPointIP() const
{
	// TODO: 在此处插入 return 语句
	return mSocket->remote_endpoint().address().to_string().c_str();
}

UInt16 NSDevilX::NSCore::INetworkConnectionImp::getEndPointPort() const
{
	return mSocket->remote_endpoint().port();
}

void NSDevilX::NSCore::INetworkConnectionImp::send(ConstVoidPtr data,SizeT sizeInBytes)
{
	auto buf=new UInt8[sizeInBytes];
	memcpy(buf,data,sizeInBytes);
	asio::async_write(*mSocket,asio::buffer(buf,sizeInBytes),[buf,this](const asio::error_code& ec,std::size_t bytes_transferred)
	{
		if(ec)
		{
#ifdef _MSC_VER
			OutputDebugStringA(("\r\nINetworkConnectionImp::send:"+ec.message()+"\r\n").c_str());
#endif
			mValidate=False;
		}
		delete buf;
	});
}

ConstVoidPtr NSDevilX::NSCore::INetworkConnectionImp::getReceivedData() const
{
	return mReceives.empty()?nullptr:&mReceives[0];
}

SizeT NSDevilX::NSCore::INetworkConnectionImp::getReceivedSizeInBytes() const
{
	return mReceives.size();
}

Void NSDevilX::NSCore::INetworkConnectionImp::received(SizeT sizeInBytes)
{
	if(sizeInBytes>0)
		mReceives.erase(mReceives.begin(),mReceives.begin()+sizeInBytes-1);
}

Void NSDevilX::NSCore::INetworkConnectionImp::_read(INetworkConnectionImp * connection,const asio::error_code & error,std::size_t bytes_transferred)
{
	if(!error)
	{
		if(bytes_transferred)
		{
			connection->mReceives.resize(connection->mReceives.size()+bytes_transferred);
			memcpy(&connection->mReceives[connection->mReceives.size()-bytes_transferred],&connection->mReceiveTemp[0],bytes_transferred);
			connection->mSocket->async_read_some(asio::buffer(&connection->mReceiveTemp[0],4096),std::bind(_read,connection,std::placeholders::_1,std::placeholders::_2));
		}
	}
	else
	{
#ifdef _MSC_VER
		OutputDebugStringA(("\r\nINetworkConnectionImp::_read:"+error.message()+"\r\n").c_str());
#endif
		connection->mValidate=False;
	}
}
