#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::CLinkImp(ILinkImp * interfaceImp,SOCKET s)
	:TInterfaceObject<ILinkImp>(interfaceImp)
	,mLinker(nullptr)
{
	mLinker=DEVILX_NEW CLinker(s);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ILinkImp>*>(this),ILinkImp::EMessage_EndPushSendData);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::~CLinkImp()
{
	DEVILX_DELETE(getLinker());
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::onMessage(ILinkImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ILinkImp::EMessage_EndPushSendData:
		if(getLinker())
			_sendData();
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		if(getLinker())
		{
			_recvData();
			_sendData();
		}
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::_sendData()
{
	for(const auto & data:getInterfaceImp()->getSendDatas())
	{
		mLinker->addSendData(&data[0],data.size());
	}
	getInterfaceImp()->getSendDatas().clear();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::_recvData()
{
	mLinker->getReceiveDatas().lockWrite();
	for(const auto & data:mLinker->getReceiveDatas())
	{
		getInterfaceImp()->addReceiveData(data);
	}
	mLinker->getReceiveDatas().clear();
	mLinker->getReceiveDatas().unLockWrite();
}