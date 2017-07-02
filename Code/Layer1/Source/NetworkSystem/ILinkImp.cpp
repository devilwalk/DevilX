#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::ILinkImp::ILinkImp(const String & destIP,UInt16 destPort,UInt16 srcPort)
	:mDestIP(destIP)
	,mDestPort(destPort)
	,mSrcPort(srcPort)
{}

NSDevilX::NSNetworkSystem::ILinkImp::~ILinkImp()
{
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getDestIP() const
{
	// TODO: insert return statement here
	return mDestIP;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getDestPort() const
{
	return mDestPort;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getSrcPort() const
{
	return mSrcPort;
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
