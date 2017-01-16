#include "Precompiler.h"
using namespace NSDevilX;
NSDevilX::CTransform2DNode::CTransform2DNode()
	:mDirtyFlag(0)
{}

NSDevilX::CTransform2DNode::~CTransform2DNode()
{}

Void NSDevilX::CTransform2DNode::setPosition(DirectX::FXMVECTOR position)
{
	if(mLocal.setPosition(position))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat2 & NSDevilX::CTransform2DNode::getPosition() const
{
	return mLocal.getPosition();
}

Void NSDevilX::CTransform2DNode::setRotation(const CRadian & radian)
{
	if(mLocal.setRotation(radian))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CRadian & NSDevilX::CTransform2DNode::getRotation() const
{
	return mLocal.getRotation();
}

Void NSDevilX::CTransform2DNode::setScale(DirectX::FXMVECTOR scale)
{
	if(mLocal.setScale(scale))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat2 & NSDevilX::CTransform2DNode::getScale() const
{
	return mLocal.getScale();
}

const CFloat2 & NSDevilX::CTransform2DNode::getUp()
{
	return mLocal.getUp();
}

const CFloat2 & NSDevilX::CTransform2DNode::getRight()
{
	return mLocal.getRight();
}

const CFloat2 & NSDevilX::CTransform2DNode::getDerivedUp()
{
	if(getParent())
	{
		_update();
		return mDerived.getUp();
	}
	else
	{
		return mLocal.getUp();
	}
}

const CFloat2 & NSDevilX::CTransform2DNode::getDerivedRight()
{
	if(getParent())
	{
		_update();
		return mDerived.getRight();
	}
	else
	{
		return mLocal.getRight();
	}
}

const CFloat2 & NSDevilX::CTransform2DNode::getDerivedPosition()
{
	if(getParent())
	{
		_update();
		return mDerived.getPosition();
	}
	else
	{
		return mLocal.getPosition();
	}
}

const CRadian & NSDevilX::CTransform2DNode::getDerivedRotation()
{
	if(getParent())
	{
		_update();
		return mDerived.getRotation();
	}
	else
	{
		return mLocal.getRotation();
	}
}

const CMatrix4F & NSDevilX::CTransform2DNode::getDerivedTransform()
{
	_update();
	return mDerived.getTransform();
}

Void NSDevilX::CTransform2DNode::_update()
{
	if(EDirtyFlag_DerivedTransform&mDirtyFlag)
	{
		mDerived.setTransform(DirectX::XMMATRIX(mLocal.getTransform())*static_cast<CTransform2DNode*>(getParent())->getDerivedTransform());
		mDirtyFlag&=~EDirtyFlag_DerivedTransform;
	}
}

NSDevilX::CTransform3DNode::CTransform3DNode()
	:mDirtyFlag(0)
{}

NSDevilX::CTransform3DNode::~CTransform3DNode()
{
}

Void NSDevilX::CTransform3DNode::setPosition(DirectX::FXMVECTOR position)
{
	if(mLocal.setPosition(position))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat3 & NSDevilX::CTransform3DNode::getPosition() const
{
	return mLocal.getPosition();
}

Void NSDevilX::CTransform3DNode::setOrientation(DirectX::FXMVECTOR orientation)
{
	if(mLocal.setOrientation(orientation))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat4 & NSDevilX::CTransform3DNode::getOrientation() const
{
	return mLocal.getOrientation();
}

Void NSDevilX::CTransform3DNode::setScale(DirectX::FXMVECTOR scale)
{
	if(mLocal.setScale(scale))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat3 & NSDevilX::CTransform3DNode::getScale() const
{
	return mLocal.getScale();
}

Void NSDevilX::CTransform3DNode::setDirection(DirectX::FXMVECTOR direction,DirectX::FXMVECTOR up)
{
	DirectX::XMVECTOR right_vec=DirectX::XMVector3Cross(up,direction);
	DirectX::XMVECTOR new_up_vec=DirectX::XMVector3Cross(direction,right_vec);
	CFloat3 dir(direction),right(right_vec),new_up(new_up_vec);
	DirectX::FXMMATRIX trans=DirectX::XMMatrixSet(right.x,right.y,right.z,0.0f
		,new_up.x,new_up.y,new_up.z,0.0f
		,dir.x,dir.y,dir.z,0.0f
		,0.0f,0.0f,0.0f,1.0f);
	setOrientation(DirectX::XMQuaternionRotationMatrix(trans));
}

Void NSDevilX::CTransform3DNode::setRotation(const CDegree & yaw,const CDegree & roll,const CDegree & pitch)
{
	setOrientation(DirectX::XMQuaternionRotationRollPitchYaw(pitch.valueRadian(),yaw.valueRadian(),roll.valueRadian()));
}

const CFloat3 & NSDevilX::CTransform3DNode::getDirection()
{
	return mLocal.getDirection();
}

const CFloat3 & NSDevilX::CTransform3DNode::getUp()
{
	return mLocal.getUp();
}

const CFloat3 & NSDevilX::CTransform3DNode::getRight()
{
	return mLocal.getRight();
}

const CFloat3 & NSDevilX::CTransform3DNode::getDerivedDirection()
{
	if(getParent())
	{
		_update();
		return mDerived.getDirection();
	}
	else
	{
		return mLocal.getDirection();
	}
}

const CFloat3 & NSDevilX::CTransform3DNode::getDerivedUp()
{
	if(getParent())
	{
		_update();
		return mDerived.getUp();
	}
	else
	{
		return mLocal.getUp();
	}
}

const CFloat3 & NSDevilX::CTransform3DNode::getDerivedRight()
{
	if(getParent())
	{
		_update();
		return mDerived.getRight();
	}
	else
	{
		return mLocal.getRight();
	}
}

const CFloat3 & NSDevilX::CTransform3DNode::getDerivedPosition()
{
	if(getParent())
	{
		_update();
		return mDerived.getPosition();
	}
	else
	{
		return mLocal.getPosition();
	}
}

const CFloat4 & NSDevilX::CTransform3DNode::getDerivedOrientation()
{
	if(getParent())
	{
		_update();
		return mDerived.getOrientation();
	}
	else
	{
		return mLocal.getOrientation();
	}
}

const CMatrix4F & NSDevilX::CTransform3DNode::getDerivedTransform()
{
	_update();
	return mDerived.getTransform();
}

Void NSDevilX::CTransform3DNode::_update()
{
	if(EDirtyFlag_DerivedTransform&mDirtyFlag)
	{
		mDerived.setTransform(DirectX::XMMATRIX(mLocal.getTransform())*static_cast<CTransform3DNode*>(getParent())->getDerivedTransform());
		mDirtyFlag&=~EDirtyFlag_DerivedTransform;
	}
}