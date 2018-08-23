#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::ILinkImp::ILinkImp(IPeerImp * peer,NSCore::INetworkConnection * connection)
	:mPeer(peer)
	,mConnection(connection)
	,mListener(nullptr)
{
	mRemoteIP=mConnection->getEndPointIP().c_str();
}

NSDevilX::NSNetworkSystem::ILinkImp::~ILinkImp()
{
	notify(EMessage_Destruction);
}

IPeer * NSDevilX::NSNetworkSystem::ILinkImp::getPeer() const
{
	return mPeer;
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getRemoteIP() const
{
	// TODO: 在此处插入 return 语句
	return mRemoteIP;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getRemotePort() const
{
	return mConnection->getEndPointPort();
}

Void NSDevilX::NSNetworkSystem::ILinkImp::addSendData(ConstVoidPtr data,UInt32 sizeInBytes)
{
	CProtocol protocol;
	protocol.setUserData(data,sizeInBytes);
	mConnection->send(protocol.getSendData(),protocol.getSendSizeInBytes());
}

Void NSDevilX::NSNetworkSystem::ILinkImp::setListener(ILinkListener * listener)
{
	mListener=listener;
}

ILinkListener * NSDevilX::NSNetworkSystem::ILinkImp::getListener() const
{
	return mListener;
}
