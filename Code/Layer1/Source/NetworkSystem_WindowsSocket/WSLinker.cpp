#include "Precompiler.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			namespace NSInternal
			{
				static DWORD CALLBACK readProc(LPVOID parameter)
				{
					auto linker=static_cast<CLinker*>(parameter);
					CProtocol protocol;
					Char data_buf[UINT16_MAX+1]={0};
					WSABUF buf;
					buf.len=sizeof(data_buf);
					buf.buf=data_buf;
					DWORD recv_size;
					DWORD flag=0;
					auto socket=linker->getSocket();
					while(linker->getSocket()!=INVALID_SOCKET)
					{
						SecureZeroMemory(data_buf,sizeof(data_buf));
						auto ret=WSARecv(socket,&buf,1,&recv_size,&flag,nullptr,nullptr);
						switch(ret)
						{
						case 0:
						{
							auto unparse_size=recv_size;
							auto unparse_buf=data_buf;
							while(unparse_size)
							{
								if(protocol.parse(unparse_buf,unparse_size))
								{
									linker->addRecvData(protocol.getUserData(),protocol.getUserSizeInBytes());
									unparse_buf+=protocol.getUserSizeInBytes();
									unparse_size-=protocol.getUserSizeInBytes();
								}
								else
								{
									OutputDebugStringA("\r\nreadProc:Parse Failed!!!\r\n");
									break;
								}
							}
						}
						break;
						case SOCKET_ERROR:
							OutputDebugStringA(("\r\nreadProc:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
							linker->disconnect();
						}
					}
					return 0;
				}
				static DWORD CALLBACK writeProc(LPVOID parameter)
				{
					const auto linker=static_cast<CLinker*>(parameter);
					TVector<Byte> datas;
					CProtocol protocol;
					WSABUF buf;
					DWORD send_size;
					auto socket=linker->getSocket();
					auto event_handle=linker->getWriteThreadEvent();
					while(linker->getSocket()!=INVALID_SOCKET)
					{
						WaitForSingleObject(event_handle,INFINITE);
						linker->getSendDatas().lockWrite();
						for(const auto & data:linker->getSendDatas())
						{
							protocol.setUserData(&data[0],static_cast<UInt16>(data.size()));
							datas.resize(datas.size()+protocol.getSendSizeInByts());
							memcpy(&datas[datas.size()-protocol.getSendSizeInByts()],protocol.getSendData(),protocol.getSendSizeInByts());
						}
						linker->getSendDatas().clear();
						linker->getSendDatas().unLockWrite();
						if(!datas.empty())
						{
							buf.len=static_cast<decltype(buf.len)>(datas.size());
							buf.buf=reinterpret_cast<decltype(buf.buf)>(&datas[0]);
							auto ret=WSASend(socket,&buf,1,&send_size,0,nullptr,nullptr);
							switch(ret)
							{
							case SOCKET_ERROR:
								OutputDebugStringA(("\r\nwriteProc:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
								break;
							}
							datas.clear();
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

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::CLinker(SOCKET s)
	:mSocket(s)
	,mReadThread(INVALID_HANDLE_VALUE)
	,mWriteThread(INVALID_HANDLE_VALUE)
	,mWriteThreadEvent(INVALID_HANDLE_VALUE)
	,mDisconnect(False)
{
	sockaddr_in addr;
	int name_len=sizeof(sockaddr_in);
	if(getpeername(getSocket(),reinterpret_cast<sockaddr*>(&addr),&name_len))
	{
		auto last_error=WSAGetLastError();
		OutputDebugStringA(("CLinker::CLinker::getpeername:"+CStringConverter::toString(last_error)+"\r\n").c_str());
	}
	mDestIP=inet_ntoa(addr.sin_addr);
	setActive(true);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::~CLinker()
{
	if(INVALID_SOCKET!=mSocket)
	{
		closesocket(mSocket);
		mSocket=INVALID_SOCKET;
	}
	if(INVALID_HANDLE_VALUE!=mReadThread)
	{
		WaitForSingleObject(mReadThread,INFINITE);
		CloseHandle(mReadThread);
	}
	if(INVALID_HANDLE_VALUE!=getWriteThreadEvent())
	{
		SetEvent(getWriteThreadEvent());
	}
	if(INVALID_HANDLE_VALUE!=mWriteThread)
	{
		WaitForSingleObject(mWriteThread,INFINITE);
		CloseHandle(mWriteThread);
	}
	if(INVALID_HANDLE_VALUE!=getWriteThreadEvent())
	{
		CloseHandle(getWriteThreadEvent());
		mWriteThreadEvent=INVALID_HANDLE_VALUE;
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::addSendData(ConstVoidPtr data,SizeT sizeInBytes)
{
	TVector<Byte> send_data;
	send_data.resize(sizeInBytes);
	memcpy(&send_data[0],data,sizeInBytes);
	mSendDatas.pushBackMT(send_data);
	SetEvent(getWriteThreadEvent());
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::addRecvData(ConstVoidPtr data,SizeT sizeInBytes)
{
	TVector<Byte> recv_data;
	recv_data.resize(sizeInBytes);
	memcpy(&recv_data[0],data,sizeInBytes);
	mRecvDatas.pushBackMT(recv_data);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::disconnect()
{
	closesocket(mSocket);
	mSocket=INVALID_SOCKET;
	mDisconnect=True;
	CSystem::getSingleton().removeLinkerMT(this);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::setActive(Boolean active)
{
	if(isActive()!=active)
	{
		if(active)
		{
			mWriteThreadEvent=CreateEvent(nullptr,FALSE,getSendDatas().empty()?FALSE:TRUE,nullptr);
			mReadThread=CreateThread(nullptr,0,NSInternal::readProc,this,0,nullptr);
			mWriteThread=CreateThread(nullptr,0,NSInternal::writeProc,this,0,nullptr);
		}
		else
		{
			auto save_socket=getSocket();
			mSocket=INVALID_SOCKET;
			SetEvent(getWriteThreadEvent());
			WaitForSingleObject(mReadThread,INFINITE);
			CloseHandle(mReadThread);
			mReadThread=INVALID_HANDLE_VALUE;
			WaitForSingleObject(mWriteThread,INFINITE);
			CloseHandle(mWriteThread);
			mWriteThread=INVALID_HANDLE_VALUE;
			CloseHandle(getWriteThreadEvent());
			mWriteThreadEvent=INVALID_HANDLE_VALUE;
			mSocket=save_socket;
		}
	}
}

Boolean NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::isActive() const
{
	return INVALID_HANDLE_VALUE!=mReadThread;
}
