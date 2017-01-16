#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;
NSDevilX::NSPhysicalSystem::ITransformerImp::ITransformerImp()
	:mPosition(CFloat3::sZero)
	,mOrientation(CFloat4::sIdentityQuaternion)
	,mScale(CFloat3::sOne)
{}

NSDevilX::NSPhysicalSystem::ITransformerImp::~ITransformerImp()
{}

Void NSDevilX::NSPhysicalSystem::ITransformerImp::setPosition(DirectX::FXMVECTOR position)
{
	if(position!=mPosition)
	{
		notify(EMessage_BeginPositionChange);
		mPosition=position;
		notify(EMessage_EndPositionChange);
	}
}

const CFloat3 & NSDevilX::NSPhysicalSystem::ITransformerImp::getPosition() const
{
	// TODO: insert return statement here
	return mPosition;
}

Void NSDevilX::NSPhysicalSystem::ITransformerImp::setOrientation(DirectX::FXMVECTOR orientation)
{
	if(orientation!=mOrientation)
	{
		notify(EMessage_BeginOrientationChange);
		mOrientation=orientation;
		notify(EMessage_EndOrientationChange);
	}
}

const CFloat4 & NSDevilX::NSPhysicalSystem::ITransformerImp::getOrientation() const
{
	// TODO: insert return statement here
	return mOrientation;
}

Void NSDevilX::NSPhysicalSystem::ITransformerImp::setScale(DirectX::FXMVECTOR scale)
{
	if(scale!=mScale)
	{
		notify(EMessage_BeginScaleChange);
		mScale=scale;
		notify(EMessage_EndScaleChange);
	}
}

const CFloat3 & NSDevilX::NSPhysicalSystem::ITransformerImp::getScale() const
{
	// TODO: insert return statement here
	return mScale;
}
