#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CNetworkManager::CNetworkManager()
	:mCurrentNotifyUnprocessedConnection(nullptr)
{
	mIOContext.run();
}

NSDevilX::NSCore::CNetworkManager::~CNetworkManager()
{
	mUnprocessedConnections.destroyAll();
}

Void NSDevilX::NSCore::CNetworkManager::update()
{
	for(auto const & acceptor_pair:mAcceptors)
	{
		for(auto s:acceptor_pair.second->getConnectedSockets())
		{
			mUnprocessedConnections.push_back(new INetworkConnectionImp(s));
		}
		acceptor_pair.second->getConnectedSocketsRef().clear();
	}
	TVector<INetworkConnectionImp*> unprocesses;
	unprocesses.reserve(mUnprocessedConnections.size());
	while(!mUnprocessedConnections.empty())
	{
		mCurrentNotifyUnprocessedConnection=mUnprocessedConnections.front();
		mUnprocessedConnections.pop_front();
		notify(EMessage_UnprocessedConnection,mCurrentNotifyUnprocessedConnection);
		if(mCurrentNotifyUnprocessedConnection)
			unprocesses.push_back(mCurrentNotifyUnprocessedConnection);
	}
	mCurrentNotifyUnprocessedConnection=nullptr;
	for(auto connecton:unprocesses)
		mUnprocessedConnections.push_back(connecton);
}

NSDevilX::NSCore::CNetworkAcceptor * NSDevilX::NSCore::CNetworkManager::createAcceptor(UInt16 port)
{
	assert(nullptr==getAcceptor(port));
	auto ret=new CNetworkAcceptor(port);
	mAcceptors.add(port,ret);
	return ret;
}

NSDevilX::Void NSDevilX::NSCore::CNetworkManager::destroyAcceptor(CNetworkAcceptor * acceptor)
{
	mAcceptors.destroy(acceptor->getPort());
}

Void NSDevilX::NSCore::CNetworkManager::createConnection(const std::string & endPointIP,unsigned short endPointPort,unsigned short localPort,const std::string & localIP)
{
	std::shared_ptr<asio::ip::tcp::socket> s(new asio::ip::tcp::socket(CNetworkManager::getSingleton().getIOContext()));
	if((static_cast<UInt16>(-1)!=localPort)&&(localIP!=""))
	{
		asio::ip::tcp::endpoint local_end_point(asio::ip::make_address(localIP),localPort);
		s->bind(local_end_point);
	}
	asio::ip::tcp::endpoint remote_end_point(asio::ip::make_address(endPointIP),endPointPort);
	s->async_connect(remote_end_point,[s,this](const asio::error_code& error)
	{
		if(!error)
		{
			mUnprocessedConnections.push_back(new INetworkConnectionImp(s));
		}
	});
}

Void NSDevilX::NSCore::CNetworkManager::destroyConnection(INetworkConnectionImp * connection)
{
	if(mCurrentNotifyUnprocessedConnection==connection)
	{
		mCurrentNotifyUnprocessedConnection=nullptr;
	}
	else
	{
		mUnprocessedConnections.destroy(connection);
	}
}
