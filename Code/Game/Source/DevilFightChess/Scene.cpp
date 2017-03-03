#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CScene::CScene()
{}

NSDevilX::NSFightChess::CScene::~CScene()
{}

Void NSDevilX::NSFightChess::CScene::onSearch(String destIP,UInt16 port)
{
	return Void();
}

Void NSDevilX::NSFightChess::CScene::onConnect(String destIP,UInt16 port)
{
	auto link=NSNetworkSystem::getSystem()->createLink(destIP,port);
	auto actor=DEVILX_NEW CActor(this,link);
	mActors.push_back(actor);
}

Void NSDevilX::NSFightChess::CScene::onDeconnect(NSNetworkSystem::ILink * link)
{
	for(auto iter=mActors.begin();mActors.end()!=iter;++iter)
	{
		auto actor=*iter;
		if(actor->getLink()==link)
		{
			mActors.erase(iter);
			DEVILX_DELETE(actor);
			break;
		}
	}
}
