#include "Precompiler.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			namespace NSInternal
			{
				struct SConnectTestParameter
					:public TBaseObject<SConnectTestParameter>
				{
					String mIP;
					UInt16 mPort;
				};
				static DWORD CALLBACK connectTest(LPVOID parameter)
				{
					auto p=static_cast<SConnectTestParameter*>(parameter);
					const auto ip=p->mIP;
					const auto port=p->mPort;
					DEVILX_DELETE(p);
					sockaddr_in addr;
					addr.sin_addr.S_un.S_addr=inet_addr(ip.c_str());
					addr.sin_family=AF_INET;
					addr.sin_port=htons(port);
					Boolean loop=true;
					while(loop)
					{
						auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
						if(0==WSAConnect(s,reinterpret_cast<const sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
						{
							auto linker=CSystemImp::getSingleton().createLinkerMT(s);
							CSystemImp::getSingleton().addSearchLinkerMT(linker);
							loop=false;
						}
						else
						{
							auto last_error=WSAGetLastError();
							if(WSAEISCONN==last_error)
								Sleep(1000);
							else
							{
								loop=false;
							}
						}
						closesocket(s);
					}
					return 0;
				}
				struct SSearchParameter
					:public TBaseObject<SSearchParameter>
				{
					String mServerIP;
					UInt16 mServerPortStart;
					UInt16 mServerPortEnd;
				};
				static DWORD CALLBACK search(LPVOID parameter)
				{
					auto search_param=static_cast<const SSearchParameter*>(parameter);
					const auto port_start=search_param->mServerPortStart;
					const auto port_end=search_param->mServerPortEnd;
					const auto ip=search_param->mServerIP;
					DEVILX_DELETE(search_param);
					for(UInt16 port=port_start;port<=port_end;++port)
					{
						NSInternal::SConnectTestParameter * parameter=DEVILX_NEW NSInternal::SConnectTestParameter();
						parameter->mIP=ip;
						parameter->mPort=port;
						CloseHandle(CreateThread(nullptr,0,NSInternal::connectTest,parameter,0,nullptr));
					}
					return 0;
				}
				static DWORD CALLBACK ioProc(LPVOID parameter)
				{
					const HANDLE io_complete_port=CSystemImp::getSingleton().getIOCompletePort();
					auto & linkers_ref=CSystemImp::getSingleton().getLinkersRef();
					while(False==ISystemImp::getSingleton().isExit())
					{
						linkers_ref.lockRead();
						for(auto linker:linkers_ref)
						{
							if(linker->isDisconnect())
								continue;
							linker->getSendBuffer().lockWrite();
							auto overlapped=new WSAOVERLAPPED;
							SecureZeroMemory(overlapped,sizeof(WSAOVERLAPPED));
							overlapped->Pointer=DEVILX_NEW CLinker::SIOComplete(CLinker::SIOComplete::EType_Send);
							static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.len=static_cast<ULONG>(linker->getSendBuffer().size());
							if(static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.len>0)
							{
								static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.buf=static_cast<Char*>(DEVILX_ALLOC(static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.len));
								CopyMemory(static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.buf,&linker->getSendBuffer()[0],static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.len);
							}
							linker->getSendBuffer().clear();
							linker->getSendBuffer().unLockWrite();
							if(static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.len>0)
							{
								auto ret=WSASend(linker->getSocket(),&static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer,1,&static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mIOSize,0,overlapped,nullptr);
								switch(ret)
								{
								case SOCKET_ERROR:
									switch(WSAGetLastError())
									{
									case WSA_IO_PENDING:break;
									default:
										OutputDebugStringA(("\r\nwriteProc:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
										linker->disconnect();
									}
								}
							}
						}
						linkers_ref.unLockRead();
						DWORD transform_bytes=0;
						CLinker * linker=nullptr;
						LPOVERLAPPED overlapped=nullptr;
						if(GetQueuedCompletionStatus(io_complete_port,&transform_bytes,reinterpret_cast<PULONG_PTR>(&linker),&overlapped,INFINITE))
						{
							switch(static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mType)
							{
							case CLinker::SIOComplete::EType_Recv:
							{
								auto overlapped=new WSAOVERLAPPED;
								SecureZeroMemory(overlapped,sizeof(WSAOVERLAPPED));
								overlapped->Pointer=DEVILX_NEW CLinker::SIOComplete(CLinker::SIOComplete::EType_Recv);
								auto ret=WSARecv(linker->getSocket(),&static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer,1,&static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mIOSize,&static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mFlag,overlapped,nullptr);
								switch(ret)
								{
								case 0:
									linker->addRecvData(static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.buf,static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mIOSize);
									break;
								case SOCKET_ERROR:
									switch(WSAGetLastError())
									{
									case WSA_IO_PENDING:break;
									default:
										OutputDebugStringA(("\r\nreadProc:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
										DEVILX_DELETE(static_cast<CLinker::SIOComplete*>(overlapped->Pointer));
										delete overlapped;
										linker->disconnect();
									}
								}
							}
							break;
							case CLinker::SIOComplete::EType_Send:
								DEVILX_FREE(static_cast<CLinker::SIOComplete*>(overlapped->Pointer)->mBuffer.buf);
								break;
							}
							DEVILX_DELETE(static_cast<CLinker::SIOComplete*>(overlapped->Pointer));
							delete overlapped;
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
ISystem * NSDevilX::NSNetworkSystem::getSystem()
{
	if(!CSystemImp::getSingletonPtr())
		DEVILX_NEW CSystemImp;
	return ISystemImp::getSingletonPtr();
}
NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystemImp::CSystemImp()
	:mIOCompletePort(INVALID_HANDLE_VALUE)
{
	DEVILX_NEW ISystemImp;
	WSADATA data;
	WSAStartup(MAKEWORD(2,2),&data);
	mIOCompletePort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,0);
	CloseHandle(CreateThread(nullptr,0,NSInternal::ioProc,this,0,nullptr));
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_EndCreateServer);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginDestroyServer);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_EndCreateClient);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginDestroyClient);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_SearchServer);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Destruction);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_EndCreateLink);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginDestroyLink);
}
NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystemImp::~CSystemImp()
{
	PostQueuedCompletionStatus(getIOCompletePort(),-1,0,nullptr);
	mLinks.destroyAll();
	mServers.destroyAll();
	WSACleanup();
}

CLinker * NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystemImp::createLinkerMT(SOCKET s)
{
	auto ret=DEVILX_NEW CLinker(s);
	mLinkers.pushBackMT(ret);
	return ret;
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystemImp::destroyLinker(CLinker * linker)
{
	mLinkers.destroy(linker);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystemImp::addSearchLinkerMT(CLinker * linker)
{
	mSearchedLinkers.pushBackMT(linker);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystemImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		mSearchedLinkers.lockWrite();
		if(ISystemImp::getSingleton().getListener())
		{
			for(auto linker:mSearchedLinkers)
			{
				if((!linker->isDisconnect())&&ISystemImp::getSingleton().getListener()->onSearch(linker->getDestIP(),linker->getDestPort()))
				{
					auto link_imp=ISystemImp::getSingleton().createLink(linker->getDestIP(),linker->getDestPort(),"127.0.0.1",-1);
					auto link=getLink(link_imp);
					link->attach(linker);
					ISystemImp::getSingleton().getListener()->onSearched(link_imp);
				}
				else
				{
					destroyLinker(linker);
				}
			}
		}
		mSearchedLinkers.clear();
		mSearchedLinkers.unLockWrite();
		notify(EMessage_Update);
		break;
	case ISystemImp::EMessage_EndCreateServer:
		mServers.add(static_cast<IServerImp*>(data),DEVILX_NEW CServerImp(static_cast<IServerImp*>(data)));
		break;
	case ISystemImp::EMessage_BeginDestroyServer:
		mServers.destroy(static_cast<IServerImp*>(data));
		break;
	case ISystemImp::EMessage_EndCreateClient:
		mClients.add(static_cast<IClientImp*>(data),DEVILX_NEW CClientImp(static_cast<IClientImp*>(data)));
		break;
	case ISystemImp::EMessage_BeginDestroyClient:
		mClients.destroy(static_cast<IClientImp*>(data));
		break;
	case ISystemImp::EMessage_EndCreateLink:
		mLinks.add(static_cast<ILinkImp*>(data),DEVILX_NEW CLinkImp(static_cast<ILinkImp*>(data)));
		break;
	case ISystemImp::EMessage_BeginDestroyLink:
		mLinks.destroy(static_cast<ILinkImp*>(data));
		break;
	case ISystemImp::EMessage_SearchServer:
	{
		struct SSearch
		{
			const String & mServerIP;
			UInt16 mServerPortStart;
			UInt16 mServerPortEnd;
		};
		auto parameter=DEVILX_NEW NSInternal::SSearchParameter();
		parameter->mServerIP=static_cast<SSearch*>(data)->mServerIP;
		parameter->mServerPortStart=static_cast<SSearch*>(data)->mServerPortStart;
		parameter->mServerPortEnd=static_cast<SSearch*>(data)->mServerPortEnd;
		CloseHandle(CreateThread(nullptr,0,NSInternal::search,parameter,0,nullptr));
	}
	break;
	case ISystemImp::EMessage_Destruction:
		DEVILX_DELETE(this);
		break;
	}
}
