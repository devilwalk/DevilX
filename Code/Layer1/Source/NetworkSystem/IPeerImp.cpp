#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSNetworkSystem;

NSDevilX::NSNetworkSystem::IPeerImp::IPeerImp(const String & ip,UInt16 port)
	:mIP(ip)
	,mPort(port)
	,mHost(nullptr)
	,mListener(nullptr)
{
	mHost=NSCore::getSystem()->getNetworkManager()->createOrRetrieveHost(mIP.c_str());
	mHost->addListeningPort(mPort);
}

NSDevilX::NSNetworkSystem::IPeerImp::~IPeerImp()
{
	mHost->removeListeningPort(mPort);
}

const String & NSDevilX::NSNetworkSystem::IPeerImp::getIP() const
{
	// TODO: 在此处插入 return 语句
	return mIP;
}

UInt16 NSDevilX::NSNetworkSystem::IPeerImp::getPort() const
{
	return mPort;
}

Void NSDevilX::NSNetworkSystem::IPeerImp::setListener(IPeerListener * listener)
{
	mListener=listener;
}

IPeerListener * NSDevilX::NSNetworkSystem::IPeerImp::getListener() const
{
	return mListener;
}

Void NSDevilX::NSNetworkSystem::IPeerImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		for(SizeT i=0;i<mHost->getNumConnections();++i)
		{
			auto connection=mHost->getConnection(i);
			if(connection->getHostPort()==mPort)
			{
				if((!ISystemImp::getSingleton().getLink(connection))&&(!mUnprocessedConnections.has(connection)))
				{
					mUnprocessedConnections.insert(connection);
				}
			}
		}
		for(auto iter=mUnprocessedConnections.begin();mUnprocessedConnections.end()!=iter;)
		{
			auto connection=*iter;
			++iter;
			if(!connection->isValidate())
			{
				NSCore::getSystem()->getNetworkManager()->destroyConnection(connection);
			}
			else
			{
			}
		}
		break;
	}
}
