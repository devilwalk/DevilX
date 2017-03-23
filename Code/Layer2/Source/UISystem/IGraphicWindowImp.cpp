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
	mPixelStart=pixelStart;
	mPixelEnd=pixelEnd;
	auto pixel_length=getPixelEnd()-getPixelStart()+CUInt2::sOne;
	auto uv_offset=getPixelStart()/CFloat2(static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getWidth()),static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getHeight()));
	auto uv_scale=pixel_length/CFloat2(static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getWidth()),static_cast<Float>(texture->queryInterface_ITexture2DReadable()->getHeight()));
	mRenderOverlayElement->setUVTransform(uv_offset,uv_scale);
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
	}
}