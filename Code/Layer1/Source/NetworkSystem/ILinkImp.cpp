#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::ILinkImp::ILinkImp(const String & destIP,UInt16 port)
	:mDestination(destIP)
	,mPort(port)
{}

NSDevilX::NSNetworkSystem::ILinkImp::~ILinkImp()
{
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getDestination() const
{
	// TODO: insert return statement here
	return mDestination;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getPort() const
{
	return mPort;
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
