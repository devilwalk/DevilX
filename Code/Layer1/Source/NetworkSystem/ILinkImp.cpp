#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::ILinkImp::ILinkImp(const String & serverIP,UInt16 serverPort,const String & clientIP,UInt16 clientPort)
	:mClientIP(clientIP)
	,mClientPort(clientPort)
	,mServerIP(serverIP)
	,mServerPort(serverPort)
{}

NSDevilX::NSNetworkSystem::ILinkImp::~ILinkImp()
{
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getServerIP() const
{
	// TODO: insert return statement here
	return mServerIP;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getServerPort() const
{
	return mServerPort;
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getClientIP() const
{
	// TODO: 在此处插入 return 语句
	return mClientIP;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getClientPort() const
{
	return mClientPort;
}

Void NSDevilX::NSNetworkSystem::ILinkImp::pushSendData(ConstVoidPtr data,UInt32 sizeInBytes)
{
	notify(EMessage_BeginPushSendData);
	TVector<Byte> send_data;
	send_data.resize(sizeInBytes);
	memcpy(&send_data[0],data,sizeInBytes);
	mSendDatas.push_back(send_data);
	notify(EMessage_EndPushSendData);
}

UInt32 NSDevilX::NSNetworkSystem::ILinkImp::getFirstReceiveDataSizeInBytes() const
{
	return mReceiveDatas.empty()?0:static_cast<UInt32>(mReceiveDatas.front().size());
}

Void NSDevilX::NSNetworkSystem::ILinkImp::popReceiveData(VoidPtr data)
{
	memcpy(data,&mReceiveDatas.front()[0],mReceiveDatas.front().size());
	mReceiveDatas.pop_front();
}
