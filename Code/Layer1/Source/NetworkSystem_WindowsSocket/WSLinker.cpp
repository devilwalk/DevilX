#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;
using namespace NSWindowsSocket;

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::CLinker(SOCKET s)
	:mSocket(s)
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

	auto handle=CreateIoCompletionPort(reinterpret_cast<HANDLE>(getSocket()),CSystemImp::getSingleton().getIOCompletionPort(),reinterpret_cast<ULONG_PTR>(this),0);
	assert(handle==CSystemImp::getSingleton().getIOCompletionPort());
	SecureZeroMemory(&mWriteOverlapped,sizeof(mWriteOverlapped));
	mWriteOverlapped.Pointer=DEVILX_NEW SIOComplete(SIOComplete::EType_Send);
	SecureZeroMemory(&mReadOverlapped,sizeof(mReadOverlapped));
	mReadOverlapped.Pointer=DEVILX_NEW SIOComplete(SIOComplete::EType_Recv);
	auto ret=WSARecv(getSocket(),&static_cast<SIOComplete*>(mReadOverlapped.Pointer)->mBuffer,1,nullptr,&static_cast<SIOComplete*>(mReadOverlapped.Pointer)->mFlag,&mReadOverlapped,nullptr);
	switch(ret)
	{
	case SOCKET_ERROR:
		switch(WSAGetLastError())
		{
		case WSA_IO_PENDING:break;
		default:
			OutputDebugStringA(("\r\nCLinker:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
			DEVILX_DELETE(static_cast<SIOComplete*>(mReadOverlapped.Pointer));
			mReadOverlapped.Pointer=nullptr;
			disconnect();
		}
	}
}

NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::~CLinker()
{
	if(INVALID_SOCKET!=getSocket())
	{
		closesocket(mSocket);
		mSocket=INVALID_SOCKET;
	}
	DEVILX_DELETE(static_cast<SIOComplete*>(mWriteOverlapped.Pointer));
	DEVILX_DELETE(static_cast<SIOComplete*>(mReadOverlapped.Pointer));
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::addSendData(ConstVoidPtr data,SizeT sizeInBytes)
{
	mSendBufferCache.lockWrite();
	const auto index=mSendBufferCache.size();
	mSendBufferCache.resize(index+sizeInBytes);
	memcpy(&mSendBufferCache[index],data,sizeInBytes);
	mSendBufferCache.unLockWrite();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::addRecvData(ConstVoidPtr data,SizeT sizeInBytes)
{
	mRecvBufferCache.lockWrite();
	const auto index=mRecvBufferCache.size();
	mRecvBufferCache.resize(index+sizeInBytes);
	memcpy(&mRecvBufferCache[index],data,sizeInBytes);
	mRecvBufferCache.unLockWrite();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::send()
{
	if(isDisconnect())
		return;
	mSendBufferCache.lockWrite();
	static_cast<SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer.len=mSendBufferCache.size();
	if(static_cast<SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer.len>0)
	{
		mSendBuffer.resize(std::max<SizeT>(static_cast<SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer.len,mSendBuffer.size()));
		static_cast<SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer.buf=&mSendBuffer[0];
		CopyMemory(static_cast<SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer.buf,&mSendBufferCache[0],static_cast<CLinker::SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer.len);
		auto ret=WSASend(getSocket(),&static_cast<CLinker::SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer,1,nullptr,0,&mWriteOverlapped,nullptr);
		switch(ret)
		{
		case SOCKET_ERROR:
			switch(WSAGetLastError())
			{
			case WSA_IO_PENDING:break;
			default:
				OutputDebugStringA(("\r\nlinker send:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
				disconnect();
			}
			break;
		}
	}
	else
	{
		static_cast<SIOComplete*>(mWriteOverlapped.Pointer)->mBuffer.buf=nullptr;
	}
	mSendBufferCache.clear();
	mSendBufferCache.unLockWrite();
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::receive()
{
	if(isDisconnect())
		return;
	DWORD read_size_in_bytes=0;
	DWORD flag=0;
	WSAGetOverlappedResult(getSocket(),&mReadOverlapped,&read_size_in_bytes,TRUE,&flag);
	addRecvData(static_cast<CLinker::SIOComplete*>(mReadOverlapped.Pointer)->mBuffer.buf,read_size_in_bytes);
	auto ret=WSARecv(getSocket(),&static_cast<SIOComplete*>(mReadOverlapped.Pointer)->mBuffer,1,nullptr,&static_cast<SIOComplete*>(mReadOverlapped.Pointer)->mFlag,&mReadOverlapped,nullptr);
	assert(SOCKET_ERROR==ret);
	switch(WSAGetLastError())
	{
	case WSA_IO_PENDING:break;
	default:
		OutputDebugStringA(("\r\nlinker recv:"+CStringConverter::toString(WSAGetLastError())+"\r\n").c_str());
		DEVILX_DELETE(static_cast<SIOComplete*>(mReadOverlapped.Pointer));
		mReadOverlapped.Pointer=nullptr;
		disconnect();
	}
}

Void NSDevilX::NSNetworkSystem::NSWindowsSocket::CLinker::disconnect()
{
	mDisconnect=True;
}