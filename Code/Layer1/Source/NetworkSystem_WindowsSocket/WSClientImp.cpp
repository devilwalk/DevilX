#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::CClientImp(IClientImp * interfaceImp)
	:mInterfaceImp(interfaceImp)
	,mLink(nullptr)
{
	mLink=CSystemImp::getSingleton().getLink(static_cast<ILinkImp*>(getInterfaceImp()->getLink()));
	auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr=inet_addr(getInterfaceImp()->getLink()->getServerIP().c_str());
	addr.sin_family=AF_INET;
	addr.sin_port=htons(getInterfaceImp()->getLink()->getServerPort());
	if(0==WSAConnect(s,reinterpret_cast<sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
	{
		mLink->attach(CSystemImp::getSingleton().createLinkerMT(s));
	}
	else
	{
		closesocket(s);
	}
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CClientImp::~CClientImp()
{
}
