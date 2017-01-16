#include "Precompiler.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			namespace NSInternal
			{
				struct SClientConnectParameter
					:public TBaseObject<SClientConnectParameter>
				{
					CLink * mLink;
					sockaddr_in mAddress;
					UInt16 mPort;
				};
				static DWORD CALLBACK clientConnect(LPVOID parameter)
				{
					auto p=static_cast<SClientConnectParameter*>(parameter);
					const auto link=p->mLink;
					const auto addr=p->mAddress;
					const auto port=p->mPort;
					DEVILX_DELETE(p);
					Boolean is_server_info=false;

					auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,WSA_FLAG_OVERLAPPED);
					UInt16 temp_port=CSystem::getSingleton().getServerPort();
					sockaddr_in client=addr;
					client.sin_port=htons(temp_port);
					Boolean not_bind_success=true;
					while(not_bind_success=0!=bind(s,reinterpret_cast<sockaddr*>(&client),sizeof(client)))
					{
						client.sin_port=htons(++temp_port);
					}
					if(!not_bind_success)
					{
						while(false==is_server_info)
						{
							if(0==WSAConnect(s,reinterpret_cast<const sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
							{
								Char data_buf[6]={0};
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
								WSACloseEvent(over_lapped.hEvent);
								if(buf.buf[0]=='D'&&buf.buf[1]=='e'&&buf.buf[2]=='v'&&buf.buf[3]=='i'&&buf.buf[4]=='l'&&buf.buf[5]=='X')
								{
									is_server_info=true;
								}
								break;
							}
							else
							{
								auto last_error=WSAGetLastError();
								if(WSAEISCONN==last_error)
									Sleep(1000);
								else
									break;
							}
						}
					}
					closesocket(s);
					if(is_server_info)
					{
						link->setServerPort(port);
					}
					return 0;
				}
				static DWORD CALLBACK findConnect(LPVOID parameter)
				{
					auto link=static_cast<CLink*>(parameter);
					for(UInt16 port=49152;port<static_cast<decltype(port)>(-1)&&(0==link->getServerPort());++port)
					{
						if(CSystem::getSingleton().getServerPort()==port)
							continue;
						NSInternal::SClientConnectParameter * parameter=DEVILX_NEW NSInternal::SClientConnectParameter;
						parameter->mLink=link;
						parameter->mAddress.sin_addr.S_un.S_addr=inet_addr(link->getInterfaceImp()->getDestination().c_str());
						parameter->mAddress.sin_family=AF_INET;
						parameter->mAddress.sin_port=htons(port);
						parameter->mPort=port;
						CloseHandle(CreateThread(nullptr,0,NSInternal::clientConnect,parameter,0,nullptr));
						Sleep(100);
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

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::CLink(ILinkImp * interfaceImp)
	:TInterfaceObject<ILinkImp>(interfaceImp)
	,mLinker(nullptr)
	,mServerPort(0)
	,mFindConnectThread(INVALID_HANDLE_VALUE)
{
	mFindConnectThread=CreateThread(nullptr,0,NSInternal::findConnect,this,0,nullptr);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ILinkImp>*>(this),ILinkImp::EMessage_EndPushSendData);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::~CLink()
{
	WaitForSingleObject(mFindConnectThread,INFINITE);
	CloseHandle(mFindConnectThread);
	DEVILX_DELETE(mLinker);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::setServerPort(UInt16 port)
{
	mServerPort.write(port);
	auto s=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,nullptr,0,0);
	auto client_port=CSystem::getSingleton().getServerPort();
	sockaddr_in client;
	client.sin_addr.S_un.S_addr=inet_addr(getInterfaceImp()->getDestination().c_str());
	client.sin_family=AF_INET;
	client.sin_port=htons(client_port);
	while(bind(s,reinterpret_cast<sockaddr*>(&client),sizeof(client)))
	{
		client.sin_port=htons(++client_port);
	}
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr=inet_addr(getInterfaceImp()->getDestination().c_str());
	addr.sin_family=AF_INET;
	addr.sin_port=htons(mServerPort);
	if(0==WSAConnect(s,reinterpret_cast<sockaddr*>(&addr),sizeof(addr),nullptr,nullptr,nullptr,nullptr))
	{
		mLinker=DEVILX_NEW CLinker(s);
		mLinker->addListener(static_cast<TMessageReceiver<CLinker>*>(this),CLinker::EMessage_BeginDestruction);
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::onMessage(ILinkImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ILinkImp::EMessage_EndPushSendData:
		if(mLinker)
		{
			_sendData();
		}
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::onMessage(CLinker * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CLinker::EMessage_BeginDestruction:
		mLinker=nullptr;
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		if(mLinker)
		{
			_recvData();
			_sendData();
		}
		break;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::_sendData()
{
	for(const auto & data:getInterfaceImp()->getSendDatas())
	{
		mLinker->addSendData(&data[0],data.size());
	}
	getInterfaceImp()->getSendDatas().clear();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLink::_recvData()
{
	mLinker->getReceiveDatas().lockRead();
	for(const auto & data:mLinker->getReceiveDatas())
	{
		getInterfaceImp()->addReceiveData(data);
	}
	mLinker->getReceiveDatas().unLockRead();
}
