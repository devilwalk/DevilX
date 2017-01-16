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
					while(!ISystemImp::getSingleton().isExit())
					{
						auto s=WSAAccept(CSystem::getSingleton().getServerSocket(),nullptr,nullptr,nullptr,NULL);
						if(INVALID_SOCKET!=s)
						{
							const Char send_data[]={'D','e','v','i','l','X'};
							auto linker=DEVILX_NEW CLinker(s,send_data,sizeof(send_data));
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
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Destruction);
}
NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::~CSystem()
{
	closesocket(mServerSocket);
	WaitForSingleObject(mServerListenThread,INFINITE);
	CloseHandle(mServerListenThread);
	WSACleanup();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CSystem::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_EndCreateLink:
		mLinks[static_cast<ILinkImp*>(data)]=DEVILX_NEW CLink(static_cast<ILinkImp*>(data));
		break;
	case ISystemImp::EMessage_BeginDestroyLink:
		mLinks.destroy(static_cast<ILinkImp*>(data));
		break;
	case ISystemImp::EMessage_Destruction:
		DEVILX_DELETE(this);
		break;
	}
}
