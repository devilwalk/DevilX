#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchServerManager::CMatchServerManager()
{}

NSDevilX::NSFightChess::CMatchServerManager::~CMatchServerManager()
{}

CMatchServer * NSDevilX::NSFightChess::CMatchServerManager::createServer(const String & name)
{
	if(mServers.has(name))
		return nullptr;
	auto ret=DEVILX_NEW CMatchServer(name);
	mServers.add(name,ret);
	return ret;
}
