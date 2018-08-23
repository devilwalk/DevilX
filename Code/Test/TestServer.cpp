// Project.cpp : Defines the entry point for the console application.
//

#include "Utility.h"
using namespace NSDevilX;
int main()
{
	auto host_ips=NSCore::getSystem()->getNetworkManager()->getHostIPs();
	TVector(NSCore::INetworkHost*) hosts;
	for(auto const & ip:host_ips)
	{
		auto host=NSCore::getSystem()->getNetworkManager()->createOrRetrieveHost(ip);
		host->addListeningPort(16666);
		hosts.push_back(host);
	}
	SizeT num_connections=0;
	do
	{
		num_connections=0;
		NSCore::getSystem()->getNetworkManager()->update();
		for(auto host:hosts)
		{
			num_connections+=host->getNumConnections();
			TVector(NSCore::INetworkConnection*) connections;
			connections.reserve(host->getNumConnections());
			for(SizeT i=0;i<host->getNumConnections();++i)
			{
				connections.push_back(host->getConnection(i));
			}
			for(auto connection:connections)
			{
				if(connection->isValidate())
				{
					String send_buf("DevilXHost");
					connection->send(&send_buf[0],send_buf.size());
				}
				else
				{
					NSCore::getSystem()->getNetworkManager()->destroyConnection(connection);
				}
			}
		}
	}while(true);
	return 0;
}

