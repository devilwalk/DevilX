#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IGraphicWindowImp::IGraphicWindowImp(const String & name)
	:mElement(nullptr)
	,mImage(nullptr)
	,mColour(CColour::sWhite)
	,mRenderRectangle(nullptr)
	,mUVStart(CFloat2::sZero)
	,mUVEnd(CFloat2::sOne)
{
	mElement=DEVILX_NEW IElementImp(name);
	mElement->addListener(this,IElementImp::EMessage_EndPositionChange);
	mElement->addListener(this,IElementImp::EMessage_EndSizeChange);
}

NSDevilX::NSUISystem::IGraphicWindowImp::~IGraphicWindowImp()
{
	DEVILX_DELETE(mImage);
	DEVILX_DELETE(mElement);
}

IElement * NSDevilX::NSUISystem::IGraphicWindowImp::queryInterface_IElement() const
{
	return mElement;
}

Void NSDevilX::NSUISystem::IGraphicWindowImp::setImage(const CImage * img,DirectX::FXMVECTOR pixelStartVec,DirectX::FXMVECTOR pixelEndVec)
{
	if(img)
	{
		mImage=img;
		DirectX::XMVECTOR img_size_vec=CFloat2(static_cast<Float>(mImage->getWidth()),static_cast<Float>(mImage->getHeight()));
		mUVStart=pixelStartVec/img_size_vec;
		mUVEnd=pixelEndVec/img_size_vec;
	}
	else
	{
		mImage=nullptr;
	}
}

Void NSDevilX::NSUISystem::IGraphicWindowImp::setColour(const CColour & colour)
{
	if(colour!=getColour())
	{
		mColour=colour;
	}
}

const CColour & NSDevilX::NSUISystem::IGraphicWindowImp::getColour() const
{
	// TODO: 在此处插入 return 语句
	return mColour;
}

Void NSDevilX::NSUISystem::IGraphicWindowImp::onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IElementImp::EMessage_EndPositionChange:
	case IElementImp::EMessage_EndSizeChange:
		_updateRenderRectangle();
		break;
	}
}

Void NSDevilX::NSUISystem::IGraphicWindowImp::_updateRenderRectangle()
{
	mRenderRectangle->setPosition(CFloat3(mElement->getPosition().x,1.0f-mElement->getPosition().y,mElement->getPosition().z)
		,CFloat3(mElement->getPosition().x+mElement->getSize().x,1.0f-mElement->getPosition().y,mElement->getPosition().z)
		,CFloat3(mElement->getPosition().x,1.0f-(mElement->getPosition().y+mElement->getSize().y),mElement->getPosition().z)
		,CFloat3(mElement->getPosition().x+mElement->getSize().x,1.0f-(mElement->getPosition().y+mElement->getSize().y),mElement->getPosition().z)
	);
	mRenderRectangle->setTextureCoord(mUVStart,CFloat2(mUVEnd.x,mUVStart.y),CFloat2(mUVStart.x,mUVEnd.y),mUVEnd);
}
