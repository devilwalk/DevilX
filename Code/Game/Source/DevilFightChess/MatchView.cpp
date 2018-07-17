#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchView2D::CMatchView2D(CMatchScene * scene)
	:mScene(scene)
	,mRenderViewport2D(nullptr)
	,mRenderCamera2D(nullptr)
	,mRenderQuery2D(nullptr)
{
	mRenderCamera2D=mScene->getRenderScene()->createCamera(CStringConverter::toString(this)+"/2D");
	mRenderCamera2D->setProjectionType(NSRenderSystem::IEnum::EProjectionType_Ortho);
	mRenderCamera2D->setNearClipPlane(1.0f);
	mRenderCamera2D->setFarClipPlane(1000.0f);
	mRenderViewport2D=CApp::getSingleton().getRenderWindow()->queryInterface_IRenderTarget()->createViewport(CStringConverter::toString(this)+"/2D");
	mRenderViewport2D->setCamera(mRenderCamera2D);
	mRenderViewport2D->setLeft(0.2f);
	mRenderViewport2D->setWidth(0.6f);
	mRenderViewport2D->setTop(0.2f);
	mRenderViewport2D->setHeight(0.6f);
	mRenderViewport2D->setClearColour(CFloatRGBA::sZero);
	mRenderCamera2D->queryInterface_IOrthoProperty()->setWidth(getSizeInPixel().x);
	mRenderCamera2D->queryInterface_IOrthoProperty()->setHeight(getSizeInPixel().y);
	mRenderQuery2D=mRenderViewport2D->createQuery("Query");
}

NSDevilX::NSFightChess::CMatchView2D::~CMatchView2D()
{
	CApp::getSingleton().getRenderWindow()->queryInterface_IRenderTarget()->destroyViewport(mRenderViewport2D);
	mScene->getRenderScene()->destroyCamera(mRenderCamera2D);
}

Void NSDevilX::NSFightChess::CMatchView2D::move(EMoveType type) const
{
	CFloat3 offset;
	switch(type)
	{
	case EMoveType_Left:offset.x=-32;break;
	case EMoveType_Right:offset.x=32;break;
	case EMoveType_Down:offset.y=-32;break;
	case EMoveType_Up:offset.y=32;break;
	}
}

CUInt2 NSDevilX::NSFightChess::CMatchView2D::getSizeInPixel() const
{
	return CApp::getSingleton().getRenderWindow()->getWindow()->getSize()*CFloat2(mRenderViewport2D->getWidth(),mRenderViewport2D->getHeight());
}
