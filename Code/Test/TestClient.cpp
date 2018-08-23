#include "Utility.h"
using namespace NSDevilX;
int main()
{
	const auto num_host_ips=NSCore::getSystem()->getNetworkManager()->getNumHostIPs();
	TVector(NSCore::INetworkHost*) hosts;
	for(SizeT i=0;i<num_host_ips;++i)
	{
		String ip=NSCore::getSystem()->getNetworkManager()->getHostIP(i);
		auto host=NSCore::getSystem()->getNetworkManager()->createOrRetrieveHost(ip.c_str());
		host->createOrRetrieveConnection(ip.c_str(),16666);
		hosts.push_back(host);
	}
	SizeT num_connections=0;
	auto timer=NSCore::getSystem()->createTimer();
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
					String send_buf("DevilXClient");
					connection->send(&send_buf[0],send_buf.size());
				}
				else
				{
					NSCore::getSystem()->getNetworkManager()->destroyConnection(connection);
				}
			}
		}
	} while(num_connections||(timer->getDeltaInSecond()<5));
	NSCore::getSystem()->shutdown();
	return 0;
}

