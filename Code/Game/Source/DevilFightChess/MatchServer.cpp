#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchServer::CMatchServer(const String & name)
	:mName(name)
	,mServer(nullptr)
{
	mServer=NSNetworkSystem::getSystem()->createServer();
	mServer->setListener(this);
}

NSDevilX::NSFightChess::CMatchServer::~CMatchServer()
{
	NSNetworkSystem::getSystem()->destroyServer(mServer);
}

Void NSDevilX::NSFightChess::CMatchServer::_processProtocal(NSNetworkSystem::ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes)
{
	return Void();
}

Boolean NSDevilX::NSFightChess::CMatchServer::onConnect(NSNetworkSystem::IServer * server,const String & clientIP,UInt16 clientPort)
{
	return true;
}

Void NSDevilX::NSFightChess::CMatchServer::onConnected(NSNetworkSystem::IServer * server,NSNetworkSystem::ILink * link)
{
	mInvalidLinks.insert(link);
	link->setListener(this);
}

Void NSDevilX::NSFightChess::CMatchServer::onDataReceived(NSNetworkSystem::ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes)
{
	if(mInvalidLinks.has(link))
	{
		mInvalidLinks.remove(link);
		auto parsed_data=static_cast<const SConnectRequestAndResponse*>(data);
		if((dataSizeInBytes==sizeof(SConnectRequestAndResponse))
			&&(0==memcmp(parsed_data,&SConnectRequestAndResponse(),sizeof(SConnectRequestAndResponse)))
			)
		{
			mLinks.push_back(link);
			link->addSendData(&SConnectRequestAndResponse(),sizeof(SConnectRequestAndResponse));
		}
		else
		{
			mServer->close(link);
		}
	}
	else
	{
		assert(mLinks.has(link));
		_processProtocal(link,data,dataSizeInBytes);
	}
}

Void NSDevilX::NSFightChess::CMatchServer::onDeconnect(NSNetworkSystem::ILink * link)
{
	mInvalidLinks.remove(link);
	mLinks.remove(link);
}
