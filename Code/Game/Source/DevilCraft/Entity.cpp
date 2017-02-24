#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSDevilCraft;

NSDevilX::NSDevilCraft::CEntity::CEntity(const String & name,CScene * scene)
	:mName(name)
	,mScene(scene)
	,mRenderEntity(nullptr)
	,mPhysicalEntity(nullptr)
{}

NSDevilX::NSDevilCraft::CEntity::~CEntity()
{
	if(mRenderEntity)
		mScene->getRenderScene()->destroyEntity(mRenderEntity);
	if(mPhysicalEntity)
		mScene->getPhysicalScene()->destroyEntity(mPhysicalEntity);
}
