#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::CLinkImp(ILinkImp * interfaceImp)
	:TInterfaceObject<ILinkImp>(interfaceImp)
	,mLinker(nullptr)
{
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ILinkImp>*>(this),ILinkImp::EMessage_Destruction);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::~CLinkImp()
{
	if(ISystemImp::getSingleton().isExit())
		return;
	CSystemImp::getSingleton().destroyLinker(getLinker());
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::attach(CLinker * linker)
{
	assert(nullptr==getLinker());
	mLinker=linker;
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::onMessage(ILinkImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ILinkImp::EMessage_Destruction:
		DEVILX_DELETE(this);
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		if(getLinker()&&getLinker()->isDisconnect())
		{
			DEVILX_DELETE(getLinker());
			mLinker=nullptr;
		}
		if(getLinker())
		{
			_recvData();
			_sendData();
		}
		else
		{
			getInterfaceImp()->setInvalidate();
		}
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::_sendData()
{
	if(!getInterfaceImp()->getSendBufferRef().empty())
	{
		mLinker->addSendData(&getInterfaceImp()->getSendBufferRef()[0],getInterfaceImp()->getSendBufferRef().size());
		getInterfaceImp()->getSendBufferRef().clear();
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkImp::_recvData()
{
	mLinker->getRecvBufferCache().lockWrite();
	if(!mLinker->getRecvBufferCache().empty())
	{
		getInterfaceImp()->addReceivedBuffer(&mLinker->getRecvBufferCache()[0],mLinker->getRecvBufferCache().size());
		mLinker->getRecvBufferCache().clear();
	}
	mLinker->getRecvBufferCache().unLockWrite();
}