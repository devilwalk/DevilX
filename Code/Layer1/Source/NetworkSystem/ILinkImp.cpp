#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::ILinkImp::ILinkImp(const String & serverIP,UInt16 serverPort,const String & clientIP,UInt16 clientPort)
	:mClientIP(clientIP)
	,mClientPort(clientPort)
	,mServerIP(serverIP)
	,mServerPort(serverPort)
	,mIsInvalidate(False)
	,mListener(nullptr)
{}

NSDevilX::NSNetworkSystem::ILinkImp::~ILinkImp()
{
	notify(EMessage_Destruction);
}

Void NSDevilX::NSNetworkSystem::ILinkImp::addReceivedBuffer(ConstVoidPtr buffer,UInt32 bufferSizeInBytes)
{
	if(getListener())
	{
		TVector<CProtocol> protocols;
		CProtocol protocol;
		UInt32 parsed_size=0;
		while(parsed_size<bufferSizeInBytes)
		{
			protocol.parse(buffer);
			parsed_size+=protocol.getSendSizeInBytes();
			protocols.push_back(protocol);
		}
		if(parsed_size==bufferSizeInBytes)
		{
			for(size_t i=0;i<protocols.size();++i)
			{
				const auto & proto=protocols[i];
				getListener()->onDataReceived(this,proto.getUserData(),proto.getUserSizeInBytes());
			}
		}
		else
		{
			assert(0);
		}
	}
}

Void NSDevilX::NSNetworkSystem::ILinkImp::setInvalidate()
{
	if(False==mIsInvalidate)
	{
		mIsInvalidate=True;
		if(getListener())
		{
			getListener()->onDeconnect(this);
		}
	}
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getServerIP() const
{
	// TODO: insert return statement here
	return mServerIP;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getServerPort() const
{
	return mServerPort;
}

const String & NSDevilX::NSNetworkSystem::ILinkImp::getClientIP() const
{
	// TODO: �ڴ˴����� return ���
	return mClientIP;
}

UInt16 NSDevilX::NSNetworkSystem::ILinkImp::getClientPort() const
{
	return mClientPort;
}

Void NSDevilX::NSNetworkSystem::ILinkImp::addSendData(ConstVoidPtr data,UInt32 sizeInBytes)
{
	const auto index=getSendBufferRef().size();
	CProtocol protocol;
	protocol.setUserData(data,sizeInBytes);
	getSendBufferRef().resize(index+protocol.getSendSizeInBytes());
	memcpy(&getSendBufferRef()[index],protocol.getSendData(),protocol.getSendSizeInBytes());
}

Void NSDevilX::NSNetworkSystem::ILinkImp::setListener(ILinkListener * listener)
{
	mListener=listener;
}

ILinkListener * NSDevilX::NSNetworkSystem::ILinkImp::getListener() const
{
	return mListener;
}
