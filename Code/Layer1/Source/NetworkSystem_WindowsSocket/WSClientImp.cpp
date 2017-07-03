#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::CClientImp(IClientImp * interfaceImp)
	:TInterfaceObject<IClientImp>(interfaceImp)
	,mLink(nullptr)
{
	auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr=inet_addr(getInterfaceImp()->getLink()->getDestIP().c_str());
	addr.sin_family=AF_INET;
	addr.sin_port=htons(getInterfaceImp()->getLink()->getDestPort());
	if(0==WSAConnect(s,reinterpret_cast<sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
	{
		mLink=DEVILX_NEW CLinkImp(static_cast<ILinkImp*>(getInterfaceImp()->getLink()),s);
	}
	else
	{
		closesocket(s);
	}
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::~CClientImp()
{
	DEVILX_DELETE(mLink);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::onMessage(IClientImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}
