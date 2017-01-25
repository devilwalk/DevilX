#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::CRenderManager::CRenderManager(NSRenderSystem::IViewport * vp)
	:mViewport(vp)
	,mRenderableObject(nullptr)
{
	mRenderableObject=mViewport->getCamera()->queryInterface_ISceneElement()->getScene()->createRenderableObject("UISystem");
}

NSDevilX::NSUISystem::CRenderManager::~CRenderManager()
{
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
