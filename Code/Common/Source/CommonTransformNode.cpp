#include "Precompiler.h"
using namespace NSDevilX;
NSDevilX::CTransform2DNode::CTransform2DNode()
	:mDirtyFlag(0)
{
}

NSDevilX::CTransform2DNode::~CTransform2DNode()
{
}

Void NSDevilX::CTransform2DNode::setPosition(const CFloat2& position)
{
	if(mLocal.setPosition(position))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat2& NSDevilX::CTransform2DNode::getPosition() const
{
	return mLocal.getPosition();
}

Void NSDevilX::CTransform2DNode::setRotation(const CRadian& radian)
{
	if(mLocal.setRotation(radian))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CRadian& NSDevilX::CTransform2DNode::getRotation() const
{
	return mLocal.getRotation();
}

Void NSDevilX::CTransform2DNode::setScale(const CFloat2& scale)
{
	if(mLocal.setScale(scale))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat2& NSDevilX::CTransform2DNode::getScale() const
{
	return mLocal.getScale();
}

const CFloat2& NSDevilX::CTransform2DNode::getUp()
{
	return mLocal.getUp();
}

const CFloat2& NSDevilX::CTransform2DNode::getRight()
{
	return mLocal.getRight();
}

const CFloat2& NSDevilX::CTransform2DNode::getDerivedUp()
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

const CFloat2& NSDevilX::CTransform2DNode::getDerivedRight()
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

const CFloat2& NSDevilX::CTransform2DNode::getDerivedPosition()
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

const CRadian& NSDevilX::CTransform2DNode::getDerivedRotation()
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

const CFloat4x4& NSDevilX::CTransform2DNode::getDerivedTransform()
{
	_update();
	return mDerived.getTransform();
}

Void NSDevilX::CTransform2DNode::_update()
{
	if(EDirtyFlag_DerivedTransform&mDirtyFlag)
	{
		mDerived.setTransform(mLocal.getTransform()*static_cast<CTransform2DNode*>(getParent())->getDerivedTransform());
		mDirtyFlag&=~EDirtyFlag_DerivedTransform;
	}
}

NSDevilX::CTransform3DNode::CTransform3DNode()
	:mDirtyFlag(0)
{
}

NSDevilX::CTransform3DNode::~CTransform3DNode()
{
}

Void NSDevilX::CTransform3DNode::setPosition(const CFloat3& position)
{
	if(mLocal.setPosition(position))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat3& NSDevilX::CTransform3DNode::getPosition() const
{
	return mLocal.getPosition();
}

Void NSDevilX::CTransform3DNode::setOrientation(const CQuaterionF& orientation)
{
	if(mLocal.setOrientation(orientation))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CQuaterionF& NSDevilX::CTransform3DNode::getOrientation() const
{
	return mLocal.getOrientation();
}

Void NSDevilX::CTransform3DNode::setScale(const CFloat3& scale)
{
	if(mLocal.setScale(scale))
	{
		mDirtyFlag|=EDirtyFlag_DerivedTransform;
	}
}

const CFloat3& NSDevilX::CTransform3DNode::getScale() const
{
	return mLocal.getScale();
}

Void NSDevilX::CTransform3DNode::setDirection(const CFloat3& direction,const CFloat3& up)
{
	auto right_vec=CMath::cross(up,direction);
	auto new_up_vec=CMath::cross(direction,right_vec);
	CFloat3 dir(direction),right(right_vec),new_up(new_up_vec);
	auto trans=CFloat4x4(right.x,right.y,right.z,0.0f
		,new_up.x,new_up.y,new_up.z,0.0f
		,dir.x,dir.y,dir.z,0.0f
		,0.0f,0.0f,0.0f,1.0f);
	setOrientation(CQuaterionF(trans));
}

Void NSDevilX::CTransform3DNode::setRotation(const CDegree& yaw,const CDegree& roll,const CDegree& pitch)
{
	setOrientation(CMath::yawPitchRoll(yaw.valueRadian(),pitch.valueRadian(),roll.valueRadian()));
}

const CFloat3& NSDevilX::CTransform3DNode::getDirection()
{
	return mLocal.getDirection();
}

const CFloat3& NSDevilX::CTransform3DNode::getUp()
{
	return mLocal.getUp();
}

const CFloat3& NSDevilX::CTransform3DNode::getRight()
{
	return mLocal.getRight();
}

const CFloat3& NSDevilX::CTransform3DNode::getDerivedDirection()
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

const CFloat3& NSDevilX::CTransform3DNode::getDerivedUp()
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

const CFloat3& NSDevilX::CTransform3DNode::getDerivedRight()
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

const CFloat3& NSDevilX::CTransform3DNode::getDerivedPosition()
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

const CQuaterionF& NSDevilX::CTransform3DNode::getDerivedOrientation()
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

const CFloat4x4& NSDevilX::CTransform3DNode::getDerivedTransform()
{
	_update();
	return mDerived.getTransform();
}

Void NSDevilX::CTransform3DNode::_update()
{
	if(EDirtyFlag_DerivedTransform&mDirtyFlag)
	{
		mDerived.setTransform(mLocal.getTransform()*static_cast<CTransform3DNode*>(getParent())->getDerivedTransform());
		mDirtyFlag&=~EDirtyFlag_DerivedTransform;
	}
}