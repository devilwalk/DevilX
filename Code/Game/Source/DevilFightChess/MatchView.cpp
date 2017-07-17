#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchView::CMatchView(CMatchScene * scene)
	:mScene(scene)
	,mRenderViewport2D(nullptr)
	,mRenderCamera2D(nullptr)
{
	mRenderCamera2D=mScene->getRenderScene()->createCamera(CStringConverter::toString(this)+"/2D");
	mRenderCamera2D->setProjectionType(NSRenderSystem::IEnum::EProjectionType_Ortho);
	mRenderCamera2D->setNearClipPlane(1.0f);
	mRenderCamera2D->setFarClipPlane(1000.0f);
	mRenderCamera2D->queryInterface_IOrthoProperty()->setWidth(10.0f);
	mRenderCamera2D->queryInterface_IOrthoProperty()->setHeight(10.0f);
	mRenderViewport2D=CApp::getSingleton().getRenderWindow()->queryInterface_IRenderTarget()->createViewport(CStringConverter::toString(this)+"/2D");
	mRenderViewport2D->setCamera(mRenderCamera2D);
	mRenderViewport2D->setLeft(0.2f);
	mRenderViewport2D->setWidth(0.6f);
	mRenderViewport2D->setTop(0.2f);
	mRenderViewport2D->setHeight(0.6f);
	mRenderViewport2D->setClearColour(CFloatRGBA::sZero);
}

NSDevilX::NSFightChess::CMatchView::~CMatchView()
{
	CApp::getSingleton().getRenderWindow()->queryInterface_IRenderTarget()->destroyViewport(mRenderViewport2D);
	mScene->getRenderScene()->destroyCamera(mRenderCamera2D);
}
