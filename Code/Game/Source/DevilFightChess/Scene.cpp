#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CScene::CScene()
	:mRenderScene(nullptr)
	,mTerrain(nullptr)
{
	NSRenderSystem::getSystem()->createScene("Scene",NSRenderSystem::IEnum::ESceneManagerAlgorithm_Simple);
	mTerrain=DEVILX_NEW CTerrain(64,64);
}

NSDevilX::NSFightChess::CScene::~CScene()
{
	DEVILX_DELETE(mTerrain);
	NSRenderSystem::getSystem()->destroyScene(getRenderScene());
}