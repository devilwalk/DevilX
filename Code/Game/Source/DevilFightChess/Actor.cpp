#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CActor::CActor(CScene * scene,NSNetworkSystem::ILink * link)
	:mScene(scene)
	,mLink(link)
{}

NSDevilX::NSFightChess::CActor::~CActor()
{}
