#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::CLinkImp(ILinkImp * interfaceImp,SOCKET s)
	:mInterfaceImp(interfaceImp)
	,mLinker(nullptr)
{
	mLinker=DEVILX_NEW CLinker(s);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::~CLinkImp()
{
	DEVILX_DELETE(getLinker());
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		_recvData();
		_sendData();
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::_sendData()
{
	mLinker->addSendData(&getInterfaceImp()->getSendBufferRef()[0],getInterfaceImp()->getSendBufferRef().size());
	getInterfaceImp()->getSendBufferRef().clear();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::_recvData()
{
	mLinker->getReceivedBuffer().lockWrite();
	getInterfaceImp()->addReceivedBuffer(&mLinker->getReceivedBuffer()[0],mLinker->getReceivedBuffer().size());
	mLinker->getReceivedBuffer().clear();
	mLinker->getReceivedBuffer().unLockWrite();
}