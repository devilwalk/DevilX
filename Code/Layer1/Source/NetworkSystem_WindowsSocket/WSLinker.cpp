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
							if(recv_size>0)
								linker->addRecvData(data_buf,recv_size);
							break;
						case SOCKET_ERROR:
							OutputDebugStringA(("\r\nreadProc:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
							linker->disconnect();
							return 0;
						}
					}
					return 0;
				}
				static DWORD CALLBACK writeProc(LPVOID parameter)
				{
					const auto linker=static_cast<CLinker*>(parameter);
					WSABUF buf;
					DWORD send_size;
					auto socket=linker->getSocket();
					auto event_handle=linker->getWriteThreadEvent();
					while(linker->getSocket()!=INVALID_SOCKET)
					{
						WaitForSingleObject(event_handle,INFINITE);
						linker->getSendBuffer().lockWrite();
						TVector<Byte> send_buffer=linker->getSendBuffer();
						linker->getSendBuffer().clear();
						linker->getSendBuffer().unLockWrite();
						if(!send_buffer.empty())
						{
							buf.len=static_cast<decltype(buf.len)>(send_buffer.size());
							buf.buf=reinterpret_cast<decltype(buf.buf)>(&send_buffer[0]);
							auto ret=WSASend(socket,&buf,1,&send_size,0,nullptr,nullptr);
							switch(ret)
							{
							case SOCKET_ERROR:
								OutputDebugStringA(("\r\nwriteProc:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
								linker->disconnect();
								return 0;
							}
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
	mDestPort=ntohs(addr.sin_port);
	mWriteThreadEvent=CreateEvent(nullptr,FALSE,FALSE,nullptr);
	mReadThread=CreateThread(nullptr,0,NSInternal::readProc,this,0,nullptr);
	mWriteThread=CreateThread(nullptr,0,NSInternal::writeProc,this,0,nullptr);
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
	mSendBuffer.lockWrite();
	const auto index=mSendBuffer.size();
	mSendBuffer.resize(index+sizeInBytes);
	memcpy(&mSendBuffer[0],data,sizeInBytes);
	mSendBuffer.unLockWrite();
	SetEvent(getWriteThreadEvent());
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::addRecvData(ConstVoidPtr data,SizeT sizeInBytes)
{
	mRecvBuffer.lockWrite();
	const auto index=mRecvBuffer.size();
	mRecvBuffer.resize(index+sizeInBytes);
	memcpy(&mRecvBuffer[0],data,sizeInBytes);
	mRecvBuffer.unLockWrite();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::disconnect()
{
	mDisconnect=True;
}