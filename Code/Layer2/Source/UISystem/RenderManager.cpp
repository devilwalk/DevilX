#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::CRenderManager::CRenderManager(NSRenderSystem::IViewport * vp)
	:mViewport(vp)
	,mRenderableObject(nullptr)
	,mVisibleArea(nullptr)
{
	mRenderableObject=mViewport->getCamera()->queryInterface_ISceneElement()->getScene()->createRenderableObject("UISystem");
	mVisibleArea=mViewport->getCamera()->queryInterface_ISceneElement()->getScene()->createVisibleArea("UISystem");
	mVisibleArea->attachObject(mRenderableObject->queryInterface_ISceneElement());
	mVisibleArea->setBoundingBox(DirectX::BoundingBox(CFloat3::sZero,CFloat3(FLT_MAX)));
}

NSDevilX::NSUISystem::CRenderManager::~CRenderManager()
{
	mViewport->getCamera()->queryInterface_ISceneElement()->getScene()->destroyVisibleArea(mVisibleArea);
	mViewport->getCamera()->queryInterface_ISceneElement()->getScene()->destroyRenderableObject(mRenderableObject);
}

Void NSDevilX::NSUISystem::CRenderManager::addImageWindow(IGraphicWindowImp * window)
{
	return Void();
}

Void NSDevilX::NSUISystem::CRenderManager::removeImageWindow(IGraphicWindowImp * window)
{
	return Void();
}

Void NSDevilX::NSUISystem::CRenderManager::onMessage(IGraphicWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}
