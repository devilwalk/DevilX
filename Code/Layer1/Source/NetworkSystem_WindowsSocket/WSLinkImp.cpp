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

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkTo::CLinkTo(ILinkImp * interfaceImp)
	:CLink(interfaceImp)
{
	auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr=inet_addr(getInterfaceImp()->getDestination().c_str());
	addr.sin_family=AF_INET;
	addr.sin_port=htons(getInterfaceImp()->getPort());
	if(0!=WSAConnect(s,reinterpret_cast<sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
	{
		closesocket(s);
		return;
	}
	Char connect_data[]="DevilXConnect";
	Char recv_data[4096]={0};
	WSABUF recv_buf;
	recv_buf.len=sizeof(recv_data);
	recv_buf.buf=recv_data;
	DWORD recv_size;
	DWORD flag=0;
	WSAOVERLAPPED over_lapped;
	SecureZeroMemory(&over_lapped,sizeof(over_lapped));
	over_lapped.hEvent=WSACreateEvent();
	WSARecv(s,&recv_buf,1,&recv_size,&flag,&over_lapped,nullptr);
	WSAWaitForMultipleEvents(1,&over_lapped.hEvent,TRUE,5000,TRUE);
	WSAGetOverlappedResult(s,&over_lapped,&recv_size,FALSE,&flag);
	WSACloseEvent(over_lapped.hEvent);
	if((0==recv_size)
		||(sizeof(connect_data)!=recv_size)
		||memcmp(connect_data,recv_buf.buf,sizeof(connect_data)))
	{
		closesocket(s);
		return;
	}
	WSABUF send_buf;
	send_buf.buf=connect_data;
	send_buf.len=sizeof(connect_data);
	DWORD send_size;
	auto ret=WSASend(s,&send_buf,1,&send_size,0,nullptr,nullptr);
	if(0!=ret)
	{
		closesocket(s);
		return;
	}

	mLinker=DEVILX_NEW CLinker(s);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkTo::~CLinkTo()
{
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkFrom::CLinkFrom(ILinkImp * interfaceImp,CLinker * linker)
	:CLink(interfaceImp)
{
	mLinker=linker;
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinkFrom::~CLinkFrom()
{
}