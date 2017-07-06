#include "Precompiler.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			namespace NSInternal
			{
				static DWORD CALLBACK serverAccept(LPVOID parameter)
				{
					CServerImp * server=static_cast<CServerImp*>(parameter);
					Boolean loop=true;
					while(loop)
					{
						auto s=WSAAccept(server->getAcceptSocket(),nullptr,nullptr,
							[](
								IN LPWSABUF lpCallerId,
								IN LPWSABUF lpCallerData,
								IN OUT LPQOS lpSQOS,
								IN OUT LPQOS lpGQOS,
								IN LPWSABUF lpCalleeId,
								OUT LPWSABUF lpCalleeData,
								OUT GROUP FAR *g,
								IN DWORD_PTR dwCallbackData
								)
						{
							return CF_ACCEPT;
						}
							,NULL);
						if(INVALID_SOCKET==s)
						{
							switch(WSAGetLastError())
							{
							case WSAEINVAL:
								loop=false;
								break;
							}
						}
						else
						{
							auto linker=CSystemImp::getSingleton().createLinkerMT(s);
							server->addUnprocessedLinkerMT(linker);
						}
					}
					return 0;
				}
			}
		}
	}
}
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CServerImp::CServerImp(IServerImp * interfaceImp)
	:mInterfaceImp(interfaceImp)
	,mAcceptThreadHandle(INVALID_HANDLE_VALUE)
	,mAcceptSocket(INVALID_SOCKET)
{
	mAcceptSocket=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
	sockaddr_in service;
	service.sin_addr.S_un.S_addr=INADDR_ANY;
	service.sin_family=AF_INET;
	auto port=getInterfaceImp()->getPort();
	if(static_cast<UInt16>(-1)==port)
		port=1024;
	service.sin_port=htons(port);
	while(bind(getAcceptSocket(),reinterpret_cast<sockaddr*>(&service),sizeof(service)))
	{
		service.sin_port=htons(++port);
	}
	getInterfaceImp()->setPort(port);
	listen(getAcceptSocket(),SOMAXCONN);
	mAcceptThreadHandle=CreateThread(nullptr,0,NSInternal::serverAccept,this,0,nullptr);
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_Update);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CServerImp::~CServerImp()
{
	closesocket(getAcceptSocket());
	WaitForSingleObject(mAcceptThreadHandle,INFINITE);
	CloseHandle(mAcceptThreadHandle);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CServerImp::addUnprocessedLinkerMT(CLinker * linker)
{
	mUnprocessedLinkers.pushBackMT(linker);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CServerImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_Update:
		if(getInterfaceImp()->getListener())
		{
			mUnprocessedLinkers.lockWrite();
			for(auto linker:mUnprocessedLinkers)
			{
				if(getInterfaceImp()->getListener()->onConnect(getInterfaceImp(),linker->getDestIP(),linker->getDestPort()))
				{
					auto link_imp=ISystemImp::getSingleton().createLink("127.0.0.1",getInterfaceImp()->getPort(),linker->getDestIP(),linker->getDestPort());
					auto link=CSystemImp::getSingleton().getLink(link_imp);
					link->attach(linker);
					mLinks.push_back(link);
					getInterfaceImp()->getListener()->onConnected(getInterfaceImp(),link_imp);
				}
				else
				{
					CSystemImp::getSingleton().destroyLinker(linker);
				}
			}
			mUnprocessedLinkers.clear();
			mUnprocessedLinkers.unLockWrite();
		}
		break;
	}
}
