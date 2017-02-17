#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::ITransformerImp::ITransformerImp()
	:mPosition(0.0f)
	,mOrientation(0,0,0,1.0f)
	,mScale(1.0f)
	,mTransform(DirectX::XMMatrixIdentity())
{
}

NSDevilX::NSRenderSystem::ITransformerImp::~ITransformerImp()
{
	if(!ISystemImp::getSingleton().isExit())
	{
		CMessageNotifier::notify(EMessage_BeginDestruction);
		CMessageNotifier::notify(EMessage_EndDestruction);
	}
}

const CMatrix4F & NSDevilX::NSRenderSystem::ITransformerImp::getTransformMT()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_Transform);
	return mTransform;
}

Void NSDevilX::NSRenderSystem::ITransformerImp::setPosition(const CFloat3 & pos)
{
	if(pos!=mPosition)
	{
		CMessageNotifier::notify(EMessage_BeginPositionChange);
		mPosition=pos;
		addDirtyFlag(EDirtyFlag_Transform);
		CMessageNotifier::notify(EMessage_EndPositionChange);
	}
}

const CFloat3 & NSDevilX::NSRenderSystem::ITransformerImp::getPosition() const
{
	return mPosition;
}

Void NSDevilX::NSRenderSystem::ITransformerImp::setOrientation(const CFloat4 & orientation)
{
	if(mOrientation!=orientation)
	{
		CMessageNotifier::notify(EMessage_BeginOrientationChange);
		mOrientation=orientation;
		addDirtyFlag(EDirtyFlag_Transform);
		CMessageNotifier::notify(EMessage_EndOrientationChange);
	}
}

const CFloat4 & NSDevilX::NSRenderSystem::ITransformerImp::getOrientation() const
{
	return mOrientation;
}

Void NSDevilX::NSRenderSystem::ITransformerImp::setScale(const CFloat3 & scale)
{
	if(mScale!=scale)
	{
		CMessageNotifier::notify(EMessage_BeginScaleChange);
		mScale=scale;
		addDirtyFlag(EDirtyFlag_Transform);
		CMessageNotifier::notify(EMessage_EndScaleChange);
	}
}

const CFloat3 & NSDevilX::NSRenderSystem::ITransformerImp::getScale() const
{
	return mScale;
}

Boolean NSDevilX::NSRenderSystem::ITransformerImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Transform:
		DirectX::FXMMATRIX scale_matrix=DirectX::XMMatrixScalingFromVector(getScale());
		DirectX::FXMMATRIX rotate_matrix=DirectX::XMMatrixRotationQuaternion(getOrientation());
		DirectX::FXMMATRIX translate_matrix=DirectX::XMMatrixTranslationFromVector(getPosition());
		mTransform=DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(scale_matrix,rotate_matrix),translate_matrix);
		return true;
	}
	return false;
}
