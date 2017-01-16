#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::ILinkImp::ILinkImp(const String & name,const String & destIP)
	:mName(name)
	,mDestination(destIP)
{}

NSDevilX::NSNetworkSystem::ILinkImp::~ILinkImp()
{
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getDestination() const
{
	// TODO: insert return statement here
	return mDestination;
}

Void NSDevilX::NSNetworkSystem::ILinkImp::pushSendData(ConstBytePtr data,UInt32 sizeInBytes)
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

Void NSDevilX::NSNetworkSystem::ILinkImp::popReceiveData(BytePtr data)
{
	memcpy(data,&mReceiveDatas.front()[0],mReceiveDatas.front().size());
	mReceiveDatas.pop_front();
}
