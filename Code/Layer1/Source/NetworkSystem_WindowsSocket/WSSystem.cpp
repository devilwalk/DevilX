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
					Boolean is_server_info=false;
					while(false==is_server_info)
					{
						auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
						if(0==WSAConnect(s,reinterpret_cast<const sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
						{
							const Char connect_data[]="DevilXConnect";
							Char data_buf[4096]={0};
							WSABUF buf;
							buf.len=sizeof(data_buf);
							buf.buf=data_buf;
							DWORD recv_size;
							DWORD flag=0;
							WSAOVERLAPPED over_lapped;
							SecureZeroMemory(&over_lapped,sizeof(over_lapped));
							over_lapped.hEvent=WSACreateEvent();
							WSARecv(s,&buf,1,&recv_size,&flag,&over_lapped,nullptr);
							WSAWaitForMultipleEvents(1,&over_lapped.hEvent,TRUE,5000,TRUE);
							WSAGetOverlappedResult(s,&over_lapped,&recv_size,FALSE,&flag);
							WSACloseEvent(over_lapped.hEvent);
							if((sizeof(connect_data)==recv_size)&&(0==memcmp(connect_data,buf.buf,recv_size)))
							{
								is_server_info=true;
							}
							closesocket(s);
							break;
						}
						else
						{
							auto last_error=WSAGetLastError();
							if(WSAEISCONN==last_error)
								Sleep(1000);
							else
							{
								closesocket(s);
								break;
							}
						}
						closesocket(s);
					}
					if(is_server_info)
					{
						CSystem::getSingleton().addSearchPortMT(ip,port);
					}
					return 0;
				}
				struct SSearchParameter
					:public TBaseObject<SSearchParameter>
				{
					String mDestIP;
					UInt16 mPortStart;
					UInt16 mPortEnd;
				};
				static DWORD CALLBACK search(LPVOID parameter)
				{
					auto search=static_cast<const SSearchParameter*>(parameter);
					const auto port_start=search->mPortStart;
					const auto port_end=search->mPortEnd;
					const auto ip=search->mDestIP;
					DEVILX_DELETE(search);
					for(UInt16 port=port_start;port<=port_end;++port)
					{
						NSInternal::SConnectTestParameter * parameter=DEVILX_NEW NSInternal::SConnectTestParameter();
						parameter->mIP=ip;
						parameter->mPort=port;
						CloseHandle(CreateThread(nullptr,0,NSInternal::connectTest,parameter,0,nullptr));
					}
					return 0;
				}
				static DWORD CALLBACK serverAccept(LPVOID parameter)
				{
					while(!ISystemImp::getSingleton().isExit())
					{
						auto s=WSAAccept(CSystem::getSingleton().getServerSocket(),nullptr,nullptr,nullptr,NULL);
						if(INVALID_SOCKET!=s)
						{
							Char connect_data[]="DevilXConnect";
							WSABUF send_buf;
							send_buf.buf=connect_data;
							send_buf.len=sizeof(connect_data);
							DWORD send_size;
							auto ret=WSASend(s,&send_buf,1,&send_size,0,nullptr,nullptr);
							if(0!=ret)
							{
								closesocket(s);
								continue;
							}
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
								continue;
							}

							auto linker=DEVILX_NEW CLinker(s);
							CSystem::getSingleton().addLinkerMT(linker);
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
	if(!CSystem::getSingletonPtr())
		DEVILX_NEW CSystem;
	return ISystemImp::getSingletonPtr();
}
NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::CSystem()
	:mServerSocket(0)
	,mServerPort(49152)
	,mServerListenThread(INVALID_HANDLE_VALUE)
{
	DEVILX_NEW ISystemImp;
	WSADATA data;
	WSAStartup(MAKEWORD(2,2),&data);
	mServerSocket=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
	sockaddr_in service;
	service.sin_addr.S_un.S_addr=INADDR_ANY;
	service.sin_family=AF_INET;
	service.sin_port=htons(mServerPort);
	while(bind(mServerSocket,reinterpret_cast<sockaddr*>(&service),sizeof(service)))
	{
		service.sin_port=htons(++mServerPort);
	}
	listen(mServerSocket,SOMAXCONN);
	mServerListenThread=CreateThread(nullptr,0,NSInternal::serverAccept,nullptr,0,nullptr);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_EndCreateLink);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginDestroyLink);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Search);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Destruction);
}
NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::~CSystem()
{
	closesocket(mServerSocket);
	WaitForSingleObject(mServerListenThread,INFINITE);
	CloseHandle(mServerListenThread);
	WSACleanup();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::addLinkerMT(CLinker * linker)
{
	mUnprocessedLinkers.pushBackMT(linker);
	mOnConnects.pushBackMT(decltype(mOnConnects)::value_type(linker->getDestIP(),linker->getDestPort()));
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::removeLinkerMT(CLinker * linker)
{
	Boolean processed=false;
	mUnprocessedLinkers.lockWrite();
	if(mUnprocessedLinkers.has(linker))
	{
		mUnprocessedLinkers.destroy(linker);
		processed=true;
	}
	mUnprocessedLinkers.unLockWrite();
	if(!processed)
	{
		ISystemImp::getSingleton().getListener()->onDeconnect(ISystemImp::getSingleton().getLink(linker->getDestIP(),linker->getDestPort()));
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::addSearchPortMT(const String & ip,UInt16 port)
{
	mSearchPorts.lockWrite();
	mSearchPorts[ip].push_back(port);
	mSearchPorts.unLockWrite();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		mSearchPorts.lockWrite();
		if(ISystemImp::getSingleton().getListener())
		{
			for(auto const & ports:mSearchPorts)
			{
				for(auto port:ports.second)
				{
					ISystemImp::getSingleton().getListener()->onSearch(ports.first,port);
				}
			}
		}
		mSearchPorts.clear();
		mSearchPorts.unLockWrite();
		mOnConnects.lockWrite();
		if(ISystemImp::getSingleton().getListener())
		{
			for(auto const & connect:mOnConnects)
			{
				ISystemImp::getSingleton().getListener()->onConnect(connect.first,connect.second);
			}
		}
		mOnConnects.clear();
		mOnConnects.unLockWrite();
		break;
	case ISystemImp::EMessage_EndCreateLink:
	{
		auto link_imp=static_cast<ILinkImp*>(data);
		CLinker * unprocessed_linker=nullptr;
		mUnprocessedLinkers.lockWrite();
		for(auto iter=mUnprocessedLinkers.begin();mUnprocessedLinkers.end()!=iter;++iter)
		{
			auto linker=*iter;
			if((linker->getDestIP()==link_imp->getDestination())
				&&(linker->getDestPort()==link_imp->getPort()))
			{
				unprocessed_linker=linker;
				mUnprocessedLinkers.erase(iter);
				break;
			}
		}
		mUnprocessedLinkers.unLockWrite();
		if(unprocessed_linker)
			mLinks[static_cast<ILinkImp*>(data)]=DEVILX_NEW CLinkFrom(link_imp,unprocessed_linker);
		else
			mLinks[static_cast<ILinkImp*>(data)]=DEVILX_NEW CLinkTo(static_cast<ILinkImp*>(data));
	}
	break;
	case ISystemImp::EMessage_BeginDestroyLink:
		mLinks.destroy(static_cast<ILinkImp*>(data));
		break;
	case ISystemImp::EMessage_Search:
	{
		struct SSearch
		{
			const String & mDestIP;
			UInt16 mPortStart;
			UInt16 mPortEnd;
		};
		auto parameter=DEVILX_NEW NSInternal::SSearchParameter();
		parameter->mDestIP=static_cast<SSearch*>(data)->mDestIP;
		parameter->mPortStart=static_cast<SSearch*>(data)->mPortStart;
		parameter->mPortEnd=static_cast<SSearch*>(data)->mPortEnd;
		CloseHandle(CreateThread(nullptr,0,NSInternal::search,parameter,0,nullptr));
	}
	break;
	case ISystemImp::EMessage_Destruction:
		DEVILX_DELETE(this);
		break;
	}
}
