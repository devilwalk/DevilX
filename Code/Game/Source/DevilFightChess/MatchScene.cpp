#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchScene::CMatchScene()
	:mRenderScene(nullptr)
	,mMap(nullptr)
{
	NSRenderSystem::getSystem()->createScene("CMatchScene",NSRenderSystem::IEnum::ESceneManagerAlgorithm_Simple);
}

NSDevilX::NSFightChess::CMatchScene::~CMatchScene()
{
	DEVILX_DELETE(mMap);
	NSRenderSystem::getSystem()->destroyScene(getRenderScene());
}

Void NSDevilX::NSFightChess::CMatchScene::loadMap(const CDataStream * dataStream)
{
	if(dataStream)
	{

	}
	else
	{
		mMap=DEVILX_NEW CMatchMap(64,64,this);
	}
}
