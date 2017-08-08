#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IGraphicWindowImp::IGraphicWindowImp(const String & name,IGraphicSceneImp * scene)
	:mScene(scene)
	,mElement(nullptr)
	,mRenderOverlayElement(nullptr)
{
	mRenderOverlayElement=mScene->getRenderViewport()->queryInterface_IOverlay()->createElement(name);
	mElement=DEVILX_NEW IElementImp(name);
	mElement->addListener(this,IElementImp::EMessage_EndDerivedPositionChange);
	mElement->addListener(this,IElementImp::EMessage_EndDerivedSizeChange);
	mElement->addListener(this,IElementImp::EMessage_EndDerivedOrderChange);
	mElement->addListener(this,IElementImp::EMessage_EndEnableChange);
}

NSDevilX::NSUISystem::IGraphicWindowImp::~IGraphicWindowImp()
{
	mScene->getRenderViewport()->queryInterface_IOverlay()->destroyElement(mRenderOverlayElement);
	DEVILX_DELETE(mElement);
}

IElement * NSDevilX::NSUISystem::IGraphicWindowImp::queryInterface_IElement() const
{
	return mElement;
}

IGraphicScene * NSDevilX::NSUISystem::IGraphicWindowImp::getScene() const
{
	return mScene;
}

Void NSDevilX::NSUISystem::IGraphicWindowImp::setTexture(NSRenderSystem::ITexture * texture,const CUInt2 & pixelStart,const CUInt2 & pixelEnd)
{
	mRenderOverlayElement->getTextureUnitState()->setTexture(texture);
	auto pixel_start=mPixelStart=pixelStart;
	auto pixel_end=mPixelEnd=pixelEnd;
	auto pixel_length=getPixelEnd()-getPixelStart()+CUInt2::sOne;
	CFloat2 uv_start=(getPixelStart()+0.5f)/CFloat2(static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getWidth()),static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getHeight()));
	CFloat2 uv_end=(getPixelEnd()+0.5f)/CFloat2(static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getWidth()),static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getHeight()));
	mRenderOverlayElement->setUVs(uv_start,CFloat2(uv_end.x,uv_start.y),CFloat2(uv_start.x,uv_end.y),uv_end);
}

NSRenderSystem::ITexture * NSDevilX::NSUISystem::IGraphicWindowImp::getTexture() const
{
	return mRenderOverlayElement->getTextureUnitState()->getTexture();
}

const CUInt2 & NSDevilX::NSUISystem::IGraphicWindowImp::getPixelStart() const
{
	// TODO: 在此处插入 return 语句
	return mPixelStart;
}

const CUInt2 & NSDevilX::NSUISystem::IGraphicWindowImp::getPixelEnd() const
{
	// TODO: 在此处插入 return 语句
	return mPixelEnd;
}

Void NSDevilX::NSUISystem::IGraphicWindowImp::setColour(const CColour & colour)
{
	mRenderOverlayElement->getColourUnitState()->setValue(colour);
}

const CColour & NSDevilX::NSUISystem::IGraphicWindowImp::getColour() const
{
	// TODO: 在此处插入 return 语句
	return mRenderOverlayElement->getColourUnitState()->getValue();
}

Void NSDevilX::NSUISystem::IGraphicWindowImp::onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IElementImp::EMessage_EndDerivedPositionChange:
		mRenderOverlayElement->setPosition(notifier->getDerivedPosition());
		break;
	case IElementImp::EMessage_EndDerivedSizeChange:
		mRenderOverlayElement->setSize(notifier->getDerivedSize());
		break;
	case IElementImp::EMessage_EndDerivedOrderChange:
		mRenderOverlayElement->setOrder(notifier->getDerivedOrder());
		break;
	case IElementImp::EMessage_EndEnableChange:
		mRenderOverlayElement->setEnable(notifier->getEnable());
		break;
	}
}