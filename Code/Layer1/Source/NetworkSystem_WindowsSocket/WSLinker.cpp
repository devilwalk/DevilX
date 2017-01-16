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
					Char data_buf[4096]={0};
					WSABUF buf;
					buf.len=sizeof(data_buf);
					buf.buf=data_buf;
					DWORD recv_size;
					DWORD flag=0;
					while(linker->getSocket()!=INVALID_SOCKET)
					{
						SecureZeroMemory(data_buf,sizeof(data_buf));
						auto ret=WSARecv(linker->getSocket(),&buf,1,&recv_size,&flag,nullptr,nullptr);
						switch(ret)
						{
						case 0:
							if(recv_size>1)
							{
								linker->addRecvData(data_buf,recv_size);
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
					auto linker=static_cast<CLinker*>(parameter);
					Char conect_data[]={'D','e','v','i','l','X'};
					CTimer timer;
					WSABUF buf;
					DWORD send_size;
					while(linker->getSocket()!=INVALID_SOCKET)
					{
						timer.updateCurrentTime();
						linker->getSendDatas().lockRead();
						if(linker->getSendDatas().empty())
						{
							if(timer.getInMillisecond()>1000)
							{
								timer.updateLastTime();
								buf.len=sizeof(conect_data);
								buf.buf=conect_data;
							}
							else
							{
								linker->getSendDatas().unLockRead();
								continue;
							}
						}
						else
						{
							buf.len=static_cast<decltype(buf.len)>(linker->getSendDatas().front().size());
							buf.buf=reinterpret_cast<decltype(buf.buf)>(&linker->getSendDatas().front()[0]);
						}
						auto ret=WSASend(linker->getSocket(),&buf,1,&send_size,0,nullptr,nullptr);
						linker->getSendDatas().unLockRead();
						switch(ret)
						{
						case 0:
							linker->getSendDatas().lockWrite();
							if(!linker->getSendDatas().empty())
								linker->getSendDatas().pop_front();
							linker->getSendDatas().unLockWrite();
							break;
						case SOCKET_ERROR:
							OutputDebugStringA(("\r\nwriteProc:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
							break;
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

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::CLinker(SOCKET s,ConstVoidPtr initData,SizeT dataSizeInBytes)
	:mSocket(s)
	,mReadThread(INVALID_HANDLE_VALUE)
	,mWriteThread(INVALID_HANDLE_VALUE)
	,mDisconnect(False)
{
	if(initData)
	{
		addSendData(initData,dataSizeInBytes);
	}
	mReadThread=CreateThread(nullptr,0,NSInternal::readProc,this,0,nullptr);
	mWriteThread=CreateThread(nullptr,0,NSInternal::writeProc,this,0,nullptr);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::~CLinker()
{
	notify(EMessage_BeginDestruction);
	if(INVALID_SOCKET!=mSocket)
	{
		closesocket(mSocket);
		mSocket=INVALID_SOCKET;
	}
	WaitForSingleObject(mReadThread,INFINITE);
	CloseHandle(mReadThread);
	WaitForSingleObject(mWriteThread,INFINITE);
	CloseHandle(mWriteThread);
	notify(EMessage_EndDestruction);
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::addSendData(ConstVoidPtr data,SizeT sizeInBytes)
{
	TVector<Byte> send_data;
	send_data.resize(sizeInBytes);
	memcpy(&send_data[0],data,sizeInBytes);
	mSendDatas.pushBackMT(send_data);
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
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		if(mDisconnect)
		{
			DEVILX_DELETE(this);
		}
		break;
	}
}
