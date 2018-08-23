#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CTransform2DFrame::CTransform2DFrame()
	:mPosition(nullptr)
	,mRotation(nullptr)
	,mScale(nullptr)
{}

NSDevilX::CTransform2DFrame::~CTransform2DFrame()
{
	DEVILX_DELETE(mPosition);
	DEVILX_DELETE(mRotation);
	DEVILX_DELETE(mScale);
}

Void NSDevilX::CTransform2DFrame::setPosition(const CFloat2 & position)
{
	if(!mPosition)
	{
		mPosition=DEVILX_NEW CFloat2Frame(position);
		mPosition->addListener(this,EMessage_BeginValueChange);
		mPosition->addListener(this,EMessage_EndValueChange);
	}
	mPosition->setValue(position);
}

Void NSDevilX::CTransform2DFrame::setRotation(Float angle)
{
	if(!mRotation)
	{
		mRotation=DEVILX_NEW CFloatFrame(angle);
		mRotation->addListener(this,EMessage_BeginValueChange);
		mRotation->addListener(this,EMessage_EndValueChange);
	}
	mRotation->setValue(angle);
}

Void NSDevilX::CTransform2DFrame::setScale(const CFloat2 & scale)
{
	if(!mScale)
	{
		mScale=DEVILX_NEW CFloat2Frame(scale);
		mScale->addListener(this,EMessage_BeginValueChange);
		mScale->addListener(this,EMessage_EndValueChange);
	}
	mScale->setValue(scale);
}

Void NSDevilX::CTransform2DFrame::onMessage(CFrameBase * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CFrameBase::EMessage_BeginValueChange:
	case CFrameBase::EMessage_EndValueChange:
		notify(message);
		break;
	}
}

NSDevilX::CTransform3DFrame::CTransform3DFrame()
	:mPosition(nullptr)
	,mRotation(nullptr)
	,mScale(nullptr)
{}

NSDevilX::CTransform3DFrame::~CTransform3DFrame()
{
	DEVILX_DELETE(mPosition);
	DEVILX_DELETE(mRotation);
	DEVILX_DELETE(mScale);
}

Void NSDevilX::CTransform3DFrame::setPosition(const CFloat3 & position)
{
	if(!mPosition)
	{
		mPosition=DEVILX_NEW CFloat3Frame(position);
		mPosition->addListener(this,EMessage_BeginValueChange);
		mPosition->addListener(this,EMessage_EndValueChange);
	}
	mPosition->setValue(position);
}

Void NSDevilX::CTransform3DFrame::setRotation(const CFloat4 & rotation)
{
	if(!mRotation)
	{
		mRotation=DEVILX_NEW CFloat4Frame(rotation);
		mRotation->addListener(this,EMessage_BeginValueChange);
		mRotation->addListener(this,EMessage_EndValueChange);
	}
	mRotation->setValue(rotation);
}

Void NSDevilX::CTransform3DFrame::setScale(const CFloat3 & scale)
{
	if(!mScale)
	{
		mScale=DEVILX_NEW CFloat3Frame(scale);
		mScale->addListener(this,EMessage_BeginValueChange);
		mScale->addListener(this,EMessage_EndValueChange);
	}
	mScale->setValue(scale);
}

Void NSDevilX::CTransform3DFrame::onMessage(CFrameBase * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CFrameBase::EMessage_BeginValueChange:
	case CFrameBase::EMessage_EndValueChange:
		notify(message);
		break;
	}
}