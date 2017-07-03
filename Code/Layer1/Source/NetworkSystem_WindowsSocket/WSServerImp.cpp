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
						auto s=WSAAccept(server->getAcceptSocket(),nullptr,nullptr,nullptr,NULL);
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
							auto linker=DEVILX_NEW CLinker(s);
							server->addUnprocessedLinkerMT(linker);
						}
					}
					return 0;
				}
				struct SConnectTestParameter
					:public TBaseObject<SConnectTestParameter>
				{
					CServerImp * mServer;
					CLinker * mLinker;
					SConnectTestParameter(CServerImp * server,CLinker * linker)
						:mServer(server)
						,mLinker(linker)
					{}
				};
				static DWORD CALLBACK connectTest(LPVOID parameter)
				{
					auto p=static_cast<SConnectTestParameter*>(parameter);
					auto server=p->mServer;
					auto linker=p->mLinker;
					Boolean connect_success=false;
					DEVILX_DELETE(p);
					Boolean has_recv_data=false;
					Int32 test_count=500;
					do
					{
						linker->getReceiveDatas().lockRead();
						has_recv_data=!linker->getReceiveDatas().empty();
						if(has_recv_data)
						{
							auto const & data=linker->getReceiveDatas().front();
							linker->getReceiveDatas().unLockRead();
							if(server->getInterfaceImp()->getListener()->onConnect(linker->getDestIP(),linker->getDestPort(),data))
							{
								connect_success=true;
							}
							else
							{
								DEVILX_DELETE(linker);
								linker=nullptr;
							}
							break;
						}
						linker->getReceiveDatas().unLockRead();
						Sleep(10);
					}
					while((!has_recv_data)&&((--test_count)>0));
					if(connect_success)
					{
						
					}
					else if(linker!=nullptr)
					{
						server->addUnprocessedLinkerMT(linker);
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

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CServerImp::addLinkerMT(CLinker * linker)
{
	mUnvisibleLinkers.pushBackMT(linker);
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
		mUnprocessedLinkers.lockWrite();
		for(auto linker:mUnprocessedLinkers)
		{
			CloseHandle(CreateThread(nullptr,0,NSInternal::connectTest,DEVILX_NEW NSInternal::SConnectTestParameter(this,linker),0,nullptr));
		}
		mUnprocessedLinkers.clear();
		mUnprocessedLinkers.unLockWrite();
		break;
	}
}
