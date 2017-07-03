#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::CClientImp(IClientImp * interfaceImp)
	:mInterfaceImp(interfaceImp)
	,mLink(nullptr)
{
	auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr=inet_addr(getInterfaceImp()->getLink()->getServerIP().c_str());
	addr.sin_family=AF_INET;
	addr.sin_port=htons(getInterfaceImp()->getLink()->getServerPort());
	if(0==WSAConnect(s,reinterpret_cast<sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
	{
		mLink=DEVILX_NEW CLinkImp(static_cast<ILinkImp*>(getInterfaceImp()->getLink()),s);
	}
	else
	{
		closesocket(s);
	}
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_Update);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::~CClientImp()
{
	DEVILX_DELETE(mLink);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_Update:
		if(mLink->getLinker()->isDisconnect())
		{

		}
		break;
	}
}
