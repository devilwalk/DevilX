// Project.cpp : Defines the entry point for the console application.
//

#include "Common.h"
#include "NetworkSystem/INetworkSystemInterface.h"
using namespace NSDevilX;
int main()
{
	NSNetworkSystem::getSystem();
	system("pause");
	NSNetworkSystem::getSystem()->update();
	NSNetworkSystem::getSystem()->shutdown();
	return 0;
}

