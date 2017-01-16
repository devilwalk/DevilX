#pragma once
#include "CommonNode.h"
#include "CommonVectorF.h"
#include "CommonMatrix.h"
#include "CommonAngle.h"
namespace NSDevilX
{
	class CTransform2DNode
		:public CNode
	{
	public:
		enum EDirtyFlag
		{
			EDirtyFlag_DerivedTransform=1,
		};
		class CLocal
			:public TBaseObject<CLocal>
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Transform=1,
				EDirtyFlag_Up=EDirtyFlag_Transform<<1,
				EDirtyFlag_Right=EDirtyFlag_Up<<1
			};
		protected:
			CFloat2 * mPosition;
			CRadian mRotation;
			CFloat2 * mScale;
			CFloat2 * mUp;
			CFloat2 * mRight;
			CMatrix4F * mTransform;
			UInt32 mDirtyFlag;
		public:
			CLocal()
				:mPosition(nullptr)
				,mRotation(0)
				,mScale(nullptr)
				,mUp(nullptr)
				,mRight(nullptr)
				,mTransform(nullptr)
				,mDirtyFlag(0)
			{}
			~CLocal()
			{
				delete mPosition;
				delete mScale;
				delete mUp;
				delete mRight;
			}
			Boolean setPosition(DirectX::FXMVECTOR position)
			{
				if(position!=getPosition())
				{
					_getPosition()=position;
					mDirtyFlag|=EDirtyFlag_Transform;
					return true;
				}
				else
				{
					return false;
				}
			}
			const CFloat2 & getPosition()const
			{
				return mPosition?*mPosition:CFloat2::sZero;
			}
			Boolean setRotation(const CRadian & radian)
			{
				if(radian!=getRotation())
				{
					mRotation=radian;
					mDirtyFlag|=EDirtyFlag_Transform|EDirtyFlag_Up|EDirtyFlag_Right;
					return true;
				}
				else
				{
					return false;
				}
			}
			const CRadian & getRotation()const
			{
				return mRotation;
			}
			Boolean setScale(DirectX::FXMVECTOR scale)
			{
				if(scale!=getScale())
				{
					_getScale()=scale;
					mDirtyFlag|=EDirtyFlag_Transform;
					return true;
				}
				else
				{
					return false;
				}
			}
			const CFloat2 & getScale()const
			{
				return mScale?*mScale:CFloat2::sOne;
			}
			const CFloat2 & getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_getUp();
					_updateCoordAxis();
				}
				return mUp?*mUp:CFloat2::sUnitY;
			}
			const CFloat2 & getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_getRight();
					_updateCoordAxis();
				}
				return mRight?*mRight:CFloat2::sUnitX;
			}
			const CMatrix4F & getTransform()
			{
				_updateTransform();
				return mTransform?*mTransform:CMatrix4F::sIdentity;
			}
		protected:
			CFloat2 & _getPosition()
			{
				if(!mPosition)
					mPosition=new CFloat2(CFloat2::sZero);
				return *mPosition;
			}
			CFloat2 & _getScale()
			{
				if(!mScale)
					mScale=new CFloat2(CFloat2::sOne);
				return *mScale;
			}
			CFloat2 & _getUp()
			{
				if(!mUp)
					mUp=new CFloat2(CFloat2::sUnitY);
				return *mUp;
			}
			CFloat2 & _getRight()
			{
				if(!mRight)
					mRight=new CFloat2(CFloat2::sUnitX);
				return *mRight;
			}
			CMatrix4F & _getTransform()
			{
				if(!mTransform)
					mTransform=new CMatrix4F(CMatrix4F::sIdentity);
				return *mTransform;
			}
			Void _updateTransform()
			{
				if(EDirtyFlag_Transform&mDirtyFlag)
				{
					DirectX::FXMMATRIX scale_matrix=DirectX::XMMatrixScalingFromVector(getScale());
					DirectX::FXMMATRIX rotate_matrix=DirectX::XMMatrixRotationZ(getRotation());
					DirectX::FXMMATRIX translate_matrix=DirectX::XMMatrixTranslationFromVector(getPosition());
					_getTransform()=DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(scale_matrix,rotate_matrix),translate_matrix);
					mDirtyFlag&=~EDirtyFlag_Transform;
				}
			}
			Void _updateCoordAxis()
			{
				if((EDirtyFlag_Up&mDirtyFlag)
					||(EDirtyFlag_Right&mDirtyFlag)
					)
				{
					auto trans=DirectX::XMMatrixRotationZ(getRotation());
					if(mUp)
					{
						*mUp=trans.r[1];
						mDirtyFlag&=~EDirtyFlag_Up;
					}
					if(mRight)
					{
						*mRight=trans.r[0];
						mDirtyFlag&=~EDirtyFlag_Right;
					}
				}
			}
		};
		class CDerived
			:public TBaseObject<CDerived>
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Position=1,
				EDirtyFlag_Rotation=EDirtyFlag_Position<<1,
				EDirtyFlag_Scale=EDirtyFlag_Rotation<<1,
				EDirtyFlag_Up=EDirtyFlag_Scale<<1,
				EDirtyFlag_Right=EDirtyFlag_Up<<1
			};
		protected:
			CFloat2 * mPosition;
			CRadian mRotation;
			CFloat2 * mScale;
			CFloat2 * mUp;
			CFloat2 * mRight;
			CMatrix4F mTransform;
			UInt32 mDirtyFlag;
		public:
			CDerived()
				:mPosition(nullptr)
				,mRotation(0)
				,mScale(nullptr)
				,mUp(nullptr)
				,mRight(nullptr)
				,mTransform(CMatrix4F::sIdentity)
				,mDirtyFlag(0)
			{}
			~CDerived()
			{
				delete mPosition;
				delete mUp;
				delete mRight;
			}
			Void setTransform(const DirectX::XMMATRIX & trans)
			{
				if(trans!=mTransform)
				{
					mTransform=trans;
					mDirtyFlag|=EDirtyFlag_Position|EDirtyFlag_Rotation|EDirtyFlag_Scale|EDirtyFlag_Up|EDirtyFlag_Right;
				}
			}
			const CMatrix4F & getTransform()const
			{
				return mTransform;
			}
			const CFloat2 & getPosition()
			{
				if(EDirtyFlag_Position&mDirtyFlag)
				{
					_getPosition();
					_updateTransform();
				}
				return mPosition?*mPosition:CFloat2::sZero;
			}
			const CRadian & getRotation()
			{
				if(EDirtyFlag_Rotation&mDirtyFlag)
				{
					_updateTransform();
				}
				return mRotation;
			}
			const CFloat2 & getScale()
			{
				if(EDirtyFlag_Scale&mDirtyFlag)
				{
					_getScale();
					_updateTransform();
				}
				return mScale?*mScale:CFloat2::sUnitY;
			}
			const CFloat2 & getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_getUp();
					_updateCoordAxis();
				}
				return mUp?*mUp:CFloat2::sUnitY;
			}
			const CFloat2 & getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_getRight();
					_updateCoordAxis();
				}
				return mRight?*mRight:CFloat2::sUnitX;
			}
		protected:
			CFloat2 & _getPosition()
			{
				if(!mPosition)
					mPosition=new CFloat2(CFloat2::sZero);
				return *mPosition;
			}
			CFloat2 & _getScale()
			{
				if(!mScale)
					mScale=new CFloat2(CFloat2::sOne);
				return *mScale;
			}
			CFloat2 & _getUp()
			{
				if(!mUp)
					mUp=new CFloat2(CFloat2::sUnitY);
				return *mUp;
			}
			CFloat2 & _getRight()
			{
				if(!mRight)
					mRight=new CFloat2(CFloat2::sUnitX);
				return *mRight;
			}
			Void _updateTransform()
			{
				if((EDirtyFlag_Position&mDirtyFlag)
					||(EDirtyFlag_Rotation&mDirtyFlag)
					)
				{
					DirectX::XMVECTOR translate,rotate,scale;
					DirectX::XMMatrixDecompose(&scale,&rotate,&translate,getTransform());
					if(mPosition)
					{
						*mPosition=translate;
						mDirtyFlag&=~EDirtyFlag_Position;
					}
					DirectX::XMVECTOR rotate_axis;
					Float rotate_radian;
					DirectX::XMQuaternionToAxisAngle(&rotate_axis,&rotate_radian,rotate);
					assert(CFloat3::sUnitZ==rotate_axis);
					mRotation=rotate_radian;
					mDirtyFlag&=~EDirtyFlag_Rotation;
					if(mScale)
					{
						*mScale=scale;
						mDirtyFlag&=~EDirtyFlag_Scale;
					}
				}
			}
			Void _updateCoordAxis()
			{
				if((EDirtyFlag_Up&mDirtyFlag)
					||(EDirtyFlag_Right&mDirtyFlag)
					)
				{
					DirectX::FXMMATRIX trans=DirectX::XMMatrixRotationZ(getRotation());
					if(mUp)
					{
						*mUp=trans.r[1];
						mDirtyFlag&=~EDirtyFlag_Up;
					}
					if(mRight)
					{
						*mRight=trans.r[0];
						mDirtyFlag&=~EDirtyFlag_Right;
					}
				}
			}
		};
	protected:
		CLocal mLocal;
		CDerived mDerived;
		UInt32 mDirtyFlag;
	public:
		CTransform2DNode();
		virtual ~CTransform2DNode();
		Void setPosition(DirectX::FXMVECTOR position);
		const CFloat2 & getPosition()const;
		Void setRotation(const CRadian & rotation);
		const CRadian & getRotation()const;
		Void setScale(DirectX::FXMVECTOR scale);
		const CFloat2 & getScale()const;
		const CFloat2 & getUp();
		const CFloat2 & getRight();
		const CMatrix4F & getTransform();
		const CFloat2 & getDerivedUp();
		const CFloat2 & getDerivedRight();
		const CFloat2 & getDerivedPosition();
		const CRadian & getDerivedRotation();
		const CMatrix4F & getDerivedTransform();
	protected:
		Void _update();
	};
	class CTransform3DNode
		:public CNode
	{
	public:
		enum EDirtyFlag
		{
			EDirtyFlag_DerivedTransform=1,
		};
		class CLocal
			:public TBaseObject<CLocal>
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Transform=1,
				EDirtyFlag_Direction=EDirtyFlag_Transform<<1,
				EDirtyFlag_Up=EDirtyFlag_Direction<<1,
				EDirtyFlag_Right=EDirtyFlag_Up<<1
			};
		protected:
			CFloat3 * mPosition;
			CFloat4 * mOrientation;
			CFloat3 * mScale;
			CMatrix4F * mTransform;
			CFloat3 * mDirection;
			CFloat3 * mUp;
			CFloat3 * mRight;
			UInt32 mDirtyFlag;
		public:
			CLocal()
				:mPosition(nullptr)
				,mOrientation(nullptr)
				,mScale(nullptr)
				,mTransform(nullptr)
				,mDirection(nullptr)
				,mUp(nullptr)
				,mRight(nullptr)
				,mDirtyFlag(0)
			{}
			~CLocal()
			{
				delete mPosition;
				delete mOrientation;
				delete mScale;
				delete mTransform;
				delete mDirection;
				delete mUp;
				delete mRight;
			}
			Boolean setPosition(DirectX::FXMVECTOR position)
			{
				if(position!=getPosition())
				{
					_getPosition()=position;
					mDirtyFlag|=EDirtyFlag_Transform;
					return true;
				}
				else
				{
					return false;
				}
			}
			const CFloat3 & getPosition()const
			{
				return mPosition?*mPosition:CFloat3::sZero;
			}
			Boolean setOrientation(DirectX::FXMVECTOR orientation)
			{
				auto nor_orientation=DirectX::XMQuaternionNormalize(orientation);
				if(nor_orientation!=getOrientation())
				{
					_getOrientation()=nor_orientation;
					mDirtyFlag|=EDirtyFlag_Transform|EDirtyFlag_Direction|EDirtyFlag_Up|EDirtyFlag_Right;
					return true;
				}
				else
				{
					return false;
				}
			}
			const CFloat4 & getOrientation()const
			{
				return mOrientation?*mOrientation:CFloat4::sIdentityQuaternion;
			}
			Boolean setScale(DirectX::FXMVECTOR scale)
			{
				if(scale!=getScale())
				{
					_getScale()=scale;
					mDirtyFlag|=EDirtyFlag_Transform;
					return true;
				}
				else
				{
					return false;
				}
			}
			const CFloat3 & getScale()const
			{
				return mScale?*mScale:CFloat3::sOne;
			}
			const CFloat3 & getDirection()
			{
				if(EDirtyFlag_Direction&mDirtyFlag)
				{
					_getDirection();
					_updateCoordAxis();
				}
				return mDirection?*mDirection:CFloat3::sUnitZ;
			}
			const CFloat3 & getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_getUp();
					_updateCoordAxis();
				}
				return mUp?*mUp:CFloat3::sUnitY;
			}
			const CFloat3 & getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_getRight();
					_updateCoordAxis();
				}
				return mRight?*mRight:CFloat3::sUnitX;
			}
			const CMatrix4F & getTransform()
			{
				_updateTransform();
				return mTransform?*mTransform:CMatrix4F::sIdentity;
			}
		protected:
			CFloat3 & _getPosition()
			{
				if(!mPosition)
					mPosition=new CFloat3(CFloat3::sZero);
				return *mPosition;
			}
			CFloat4 & _getOrientation()
			{
				if(!mOrientation)
					mOrientation=new CFloat4(CFloat4::sIdentityQuaternion);
				return *mOrientation;
			}
			CFloat3 & _getScale()
			{
				if(!mScale)
					mScale=new CFloat3(CFloat3::sOne);
				return *mScale;
			}
			CMatrix4F & _getTransform()
			{
				if(!mTransform)
					mTransform=new CMatrix4F(CMatrix4F::sIdentity);
				return *mTransform;
			}
			CFloat3 & _getDirection()
			{
				if(!mDirection)
					mDirection=new CFloat3(CFloat3::sUnitZ);
				return *mDirection;
			}
			CFloat3 & _getUp()
			{
				if(!mUp)
					mUp=new CFloat3(CFloat3::sUnitY);
				return *mUp;
			}
			CFloat3 & _getRight()
			{
				if(!mRight)
					mRight=new CFloat3(CFloat3::sUnitX);
				return *mRight;
			}
			Void _updateTransform()
			{
				if(EDirtyFlag_Transform&mDirtyFlag)
				{
					DirectX::FXMMATRIX scale_matrix=DirectX::XMMatrixScalingFromVector(getScale());
					DirectX::FXMMATRIX rotate_matrix=DirectX::XMMatrixRotationQuaternion(getOrientation());
					DirectX::FXMMATRIX translate_matrix=DirectX::XMMatrixTranslationFromVector(getPosition());
					_getTransform()=DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(scale_matrix,rotate_matrix),translate_matrix);
					mDirtyFlag&=~EDirtyFlag_Transform;
				}
			}
			Void _updateCoordAxis()
			{
				if((EDirtyFlag_Direction&mDirtyFlag)
					||(EDirtyFlag_Up&mDirtyFlag)
					||(EDirtyFlag_Right&mDirtyFlag)
					)
				{
					DirectX::FXMMATRIX trans=DirectX::XMMatrixRotationQuaternion(getOrientation());
					if(mDirection)
					{
						*mDirection=trans.r[2];
						mDirtyFlag&=~EDirtyFlag_Direction;
					}
					if(mUp)
					{
						*mUp=trans.r[1];
						mDirtyFlag&=~EDirtyFlag_Up;
					}
					if(mRight)
					{
						*mRight=trans.r[0];
						mDirtyFlag&=~EDirtyFlag_Right;
					}
				}
			}
		};
		class CDerived
			:public TBaseObject<CDerived>
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Position=1,
				EDirtyFlag_Orientation=EDirtyFlag_Position<<1,
				EDirtyFlag_Direction=EDirtyFlag_Orientation<<1,
				EDirtyFlag_Up=EDirtyFlag_Direction<<1,
				EDirtyFlag_Right=EDirtyFlag_Up<<1
			};
		protected:
			CFloat3 * mPosition;
			CFloat4 * mOrientation;
			CFloat3 * mDirection;
			CFloat3 * mUp;
			CFloat3 * mRight;
			CMatrix4F mTransform;
			UInt32 mDirtyFlag;
		public:
			CDerived()
				:mPosition(nullptr)
				,mOrientation(nullptr)
				,mDirection(nullptr)
				,mUp(nullptr)
				,mRight(nullptr)
				,mTransform(CMatrix4F::sIdentity)
				,mDirtyFlag(0)
			{}
			~CDerived()
			{
				delete mPosition;
				delete mOrientation;
				delete mDirection;
				delete mUp;
				delete mRight;
			}
			Void setTransform(const DirectX::XMMATRIX & trans)
			{
				if(trans!=mTransform)
				{
					mTransform=trans;
					mDirtyFlag|=EDirtyFlag_Position|EDirtyFlag_Orientation|EDirtyFlag_Direction|EDirtyFlag_Up|EDirtyFlag_Right;
				}
			}
			const CMatrix4F & getTransform()const
			{
				return mTransform;
			}
			const CFloat3 & getPosition()
			{
				if(EDirtyFlag_Position&mDirtyFlag)
				{
					_getPosition();
					_updateTransform();
				}
				return mPosition?*mPosition:CFloat3::sZero;
			}
			const CFloat4 & getOrientation()
			{
				if(EDirtyFlag_Orientation&mDirtyFlag)
				{
					_getOrientation();
					_updateTransform();
				}
				return mOrientation?*mOrientation:CFloat4::sIdentityQuaternion;
			}
			const CFloat3 & getDirection()
			{
				if(EDirtyFlag_Direction&mDirtyFlag)
				{
					_getDirection();
					_updateCoordAxis();
				}
				return mDirection?*mDirection:CFloat3::sUnitZ;
			}
			const CFloat3 & getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_getUp();
					_updateCoordAxis();
				}
				return mUp?*mUp:CFloat3::sUnitY;
			}
			const CFloat3 & getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_getRight();
					_updateCoordAxis();
				}
				return mRight?*mRight:CFloat3::sUnitX;
			}
		protected:
			CFloat3 & _getPosition()
			{
				if(!mPosition)
					mPosition=new CFloat3(CFloat3::sZero);
				return *mPosition;
			}
			CFloat4 & _getOrientation()
			{
				if(!mOrientation)
					mOrientation=new CFloat4(CFloat4::sIdentityQuaternion);
				return *mOrientation;
			}
			CFloat3 & _getDirection()
			{
				if(!mDirection)
					mDirection=new CFloat3(CFloat3::sUnitZ);
				return *mDirection;
			}
			CFloat3 & _getUp()
			{
				if(!mUp)
					mUp=new CFloat3(CFloat3::sUnitY);
				return *mUp;
			}
			CFloat3 & _getRight()
			{
				if(!mRight)
					mRight=new CFloat3(CFloat3::sUnitX);
				return *mRight;
			}
			Void _updateTransform()
			{
				if((EDirtyFlag_Position&mDirtyFlag)
					||(EDirtyFlag_Orientation&mDirtyFlag)
					)
				{
					DirectX::XMVECTOR translate,rotate,scale;
					DirectX::XMMatrixDecompose(&scale,&rotate,&translate,getTransform());
					if(mPosition)
					{
						*mPosition=translate;
						mDirtyFlag&=~EDirtyFlag_Position;
					}
					if(mOrientation)
					{
						*mOrientation=rotate;
						mDirtyFlag&=~EDirtyFlag_Orientation;
					}
				}
			}
			Void _updateCoordAxis()
			{
				if((EDirtyFlag_Direction&mDirtyFlag)
					||(EDirtyFlag_Up&mDirtyFlag)
					||(EDirtyFlag_Right&mDirtyFlag)
					)
				{
					DirectX::FXMMATRIX trans=DirectX::XMMatrixRotationQuaternion(getOrientation());
					if(mDirection)
					{
						*mDirection=trans.r[2];
						mDirtyFlag&=~EDirtyFlag_Direction;
					}
					if(mUp)
					{
						*mUp=trans.r[1];
						mDirtyFlag&=~EDirtyFlag_Up;
					}
					if(mRight)
					{
						*mRight=trans.r[0];
						mDirtyFlag&=~EDirtyFlag_Right;
					}
				}
			}
		};
	protected:
		CLocal mLocal;
		CDerived mDerived;
		UInt32 mDirtyFlag;
	public:
		CTransform3DNode();
		virtual ~CTransform3DNode();
		Void setPosition(DirectX::FXMVECTOR position);
		const CFloat3 & getPosition()const;
		Void setOrientation(DirectX::FXMVECTOR orientation);
		const CFloat4 & getOrientation()const;
		Void setScale(DirectX::FXMVECTOR scale);
		const CFloat3 & getScale()const;
		Void setDirection(DirectX::FXMVECTOR direction,DirectX::FXMVECTOR up);
		Void setRotation(const CDegree & yaw,const CDegree & roll,const CDegree & pitch);
		const CFloat3 & getDirection();
		const CFloat3 & getUp();
		const CFloat3 & getRight();
		const CMatrix4F & getTransform();
		const CFloat3 & getDerivedDirection();
		const CFloat3 & getDerivedUp();
		const CFloat3 & getDerivedRight();
		const CFloat3 & getDerivedPosition();
		const CFloat4 & getDerivedOrientation();
		const CMatrix4F & getDerivedTransform();
	protected:
		Void _update();
	};
}