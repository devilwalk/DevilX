#pragma once
#include "CommonNode.h"
#include "CommonMath.h"
#include "CommonAngle.h"
namespace NSDevilX
{
	class CTransform2DNode
		:public TNode<TList<CTransform2DNode*> >
	{
	public:
		enum EDirtyFlag
		{
			EDirtyFlag_DerivedTransform=1,
		};
		class CLocal
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Transform=1,
				EDirtyFlag_Up=EDirtyFlag_Transform<<1,
				EDirtyFlag_Right=EDirtyFlag_Up<<1
			};
		protected:
			CFloat2 mPosition;
			CRadian mRotation;
			CFloat2 mScale;
			CFloat2 mUp;
			CFloat2 mRight;
			CFloat4x4 mTransform;
			UInt32 mDirtyFlag;
		public:
			CLocal()
				:mPosition(0)
				,mRotation(0)
				,mScale(1.0f)
				,mUp(0,1)
				,mRight(1,0)
				,mTransform(CMath::sFloat4x4_Identity)
				,mDirtyFlag(0)
			{}
			~CLocal()
			{
			}
			auto setPosition(const CFloat2 & position)
			{
				if(position!=mPosition)
				{
					mPosition=position;
					mDirtyFlag|=EDirtyFlag_Transform;
					return true;
				}
				else
				{
					return false;
				}
			}
			const auto& getPosition()const
			{
				return mPosition;
			}
			auto setRotation(const CRadian & radian)
			{
				if(radian!=mRotation)
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
			const auto& getRotation()const
			{
				return mRotation;
			}
			auto setScale(const CFloat2 & scale)
			{
				if(scale!=mScale)
				{
					mScale=scale;
					mDirtyFlag|=EDirtyFlag_Transform;
					return true;
				}
				else
				{
					return false;
				}
			}
			const auto& getScale()const
			{
				return mScale;
			}
			const auto& getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mUp;
			}
			const auto& getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mRight;
			}
			const auto & getTransform()
			{
				_updateTransform();
				return mTransform;
			}
		protected:
			Void _updateTransform()
			{
				if(EDirtyFlag_Transform&mDirtyFlag)
				{
					mDirtyFlag&=~EDirtyFlag_Transform;
				}
			}
			Void _updateCoordAxis()
			{
				if((EDirtyFlag_Up&mDirtyFlag)
					||(EDirtyFlag_Right&mDirtyFlag)
					)
				{
				}
			}
		};
		class CDerived
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
			CFloat2 mPosition;
			CRadian mRotation;
			CFloat2 mScale;
			CFloat2 mUp;
			CFloat2 mRight;
			CFloat4x4 mTransform;
			UInt32 mDirtyFlag;
		public:
			CDerived()
				:mPosition(0)
				,mRotation(0)
				,mScale(1)
				,mUp(0,1)
				,mRight(1,0)
				,mTransform(CMath::sFloat4x4_Identity)
				,mDirtyFlag(0)
			{}
			~CDerived()
			{
			}
			Void setTransform(const CFloat4x4& trans)
			{
				if(trans!=mTransform)
				{
					mTransform=trans;
					mDirtyFlag|=EDirtyFlag_Position|EDirtyFlag_Rotation|EDirtyFlag_Scale|EDirtyFlag_Up|EDirtyFlag_Right;
				}
			}
			const auto& getTransform()const
			{
				return mTransform;
			}
			const auto& getPosition()
			{
				if(EDirtyFlag_Position&mDirtyFlag)
				{
					_updateTransform();
				}
				return mPosition;
			}
			const auto& getRotation()
			{
				if(EDirtyFlag_Rotation&mDirtyFlag)
				{
					_updateTransform();
				}
				return mRotation;
			}
			const auto& getScale()
			{
				if(EDirtyFlag_Scale&mDirtyFlag)
				{
					_updateTransform();
				}
				return mScale;
			}
			const auto& getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mUp;
			}
			const auto& getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mRight;
			}
		protected:
			Void _updateTransform()
			{
				if((EDirtyFlag_Position&mDirtyFlag)
					||(EDirtyFlag_Rotation&mDirtyFlag)
					)
				{
				}
			}
			Void _updateCoordAxis()
			{
				if((EDirtyFlag_Up&mDirtyFlag)
					||(EDirtyFlag_Right&mDirtyFlag)
					)
				{
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
		Void setPosition(const CFloat2 & position);
		const CFloat2 & getPosition()const;
		Void setRotation(const CRadian & rotation);
		const CRadian & getRotation()const;
		Void setScale(const CFloat2 & scale);
		const CFloat2 & getScale()const;
		const CFloat2 & getUp();
		const CFloat2 & getRight();
		const CFloat4x4 & getTransform();
		const CFloat2 & getDerivedUp();
		const CFloat2 & getDerivedRight();
		const CFloat2 & getDerivedPosition();
		const CRadian & getDerivedRotation();
		const CFloat4x4& getDerivedTransform();
	protected:
		Void _update();
	};
	class CTransform3DNode
		:public TNode<TList<CTransform3DNode*> >
	{
	public:
		enum EDirtyFlag
		{
			EDirtyFlag_DerivedTransform=1,
		};
		class CLocal
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
			CFloat3 mPosition;
			CQuaterionF mOrientation;
			CFloat3 mScale;
			CFloat4x4 mTransform;
			CFloat3 mDirection;
			CFloat3 mUp;
			CFloat3 mRight;
			UInt32 mDirtyFlag;
		public:
			CLocal()
				:mPosition(0)
				,mOrientation(CMath::sQuaterionF_Identity)
				,mScale(1)
				,mTransform(CMath::sFloat4x4_Identity)
				,mDirection(CMath::sUnitZ)
				,mUp(CMath::sUnitY)
				,mRight(CMath::sUnitX)
				,mDirtyFlag(0)
			{}
			~CLocal()
			{
			}
			auto setPosition(const CFloat3 & position)
			{
				if(position!=mPosition)
				{
					mPosition=position;
					mDirtyFlag|=EDirtyFlag_Transform;
					return true;
				}
				else
				{
					return false;
				}
			}
			const auto& getPosition()const
			{
				return mPosition;
			}
			auto setOrientation(const CQuaterionF& orientation)
			{
				auto nor_orientation=CMath::normalize(orientation);
				if(nor_orientation!=mOrientation)
				{
					mOrientation=nor_orientation;
					mDirtyFlag|=EDirtyFlag_Transform|EDirtyFlag_Direction|EDirtyFlag_Up|EDirtyFlag_Right;
					return true;
				}
				else
				{
					return false;
				}
			}
			const auto& getOrientation()const
			{
				return mOrientation;
			}
			auto setScale(const CFloat3 & scale)
			{
				if(scale!=mScale)
				{
					mScale=scale;
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
				return mScale;
			}
			const CFloat3 & getDirection()
			{
				if(EDirtyFlag_Direction&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mDirection;
			}
			const CFloat3 & getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mUp;
			}
			const CFloat3 & getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mRight;
			}
			const CFloat4x4 & getTransform()
			{
				_updateTransform();
				return mTransform;
			}
		protected:
			Void _updateTransform()
			{
				if(EDirtyFlag_Transform&mDirtyFlag)
				{
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
				}
			}
		};
		class CDerived
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
			CFloat3 mPosition;
			CQuaterionF mOrientation;
			CFloat3 mDirection;
			CFloat3 mUp;
			CFloat3 mRight;
			CFloat4x4 mTransform;
			UInt32 mDirtyFlag;
		public:
			CDerived()
				:mPosition(0)
				,mOrientation(CMath::sQuaterionF_Identity)
				,mDirection(CMath::sUnitZ)
				,mUp(CMath::sUnitY)
				,mRight(CMath::sUnitX)
				,mTransform(CMath::sFloat4x4_Identity)
				,mDirtyFlag(0)
			{}
			~CDerived()
			{
			}
			Void setTransform(const CFloat4x4& trans)
			{
				if(trans!=mTransform)
				{
					mTransform=trans;
					mDirtyFlag|=EDirtyFlag_Position|EDirtyFlag_Orientation|EDirtyFlag_Direction|EDirtyFlag_Up|EDirtyFlag_Right;
				}
			}
			const auto& getTransform()const
			{
				return mTransform;
			}
			const auto& getPosition()
			{
				if(EDirtyFlag_Position&mDirtyFlag)
				{
					_updateTransform();
				}
				return mPosition;
			}
			const auto& getOrientation()
			{
				if(EDirtyFlag_Orientation&mDirtyFlag)
				{
					_updateTransform();
				}
				return mOrientation;
			}
			const auto& getDirection()
			{
				if(EDirtyFlag_Direction&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mDirection;
			}
			const auto& getUp()
			{
				if(EDirtyFlag_Up&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mUp;
			}
			const auto& getRight()
			{
				if(EDirtyFlag_Right&mDirtyFlag)
				{
					_updateCoordAxis();
				}
				return mRight;
			}
		protected:
			Void _updateTransform()
			{
				if((EDirtyFlag_Position&mDirtyFlag)
					||(EDirtyFlag_Orientation&mDirtyFlag)
					)
				{
				}
			}
			Void _updateCoordAxis()
			{
				if((EDirtyFlag_Direction&mDirtyFlag)
					||(EDirtyFlag_Up&mDirtyFlag)
					||(EDirtyFlag_Right&mDirtyFlag)
					)
				{
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
		Void setPosition(const CFloat3& position);
		const CFloat3& getPosition()const;
		Void setOrientation(const CQuaterionF& orientation);
		const CQuaterionF& getOrientation()const;
		Void setScale(const CFloat3& scale);
		const CFloat3& getScale()const;
		Void setDirection(const CFloat3& direction,const CFloat3& up);
		Void setRotation(const CDegree& yaw,const CDegree& roll,const CDegree& pitch);
		const CFloat3& getDirection();
		const CFloat3& getUp();
		const CFloat3& getRight();
		const CFloat4x4& getTransform();
		const CFloat3& getDerivedDirection();
		const CFloat3& getDerivedUp();
		const CFloat3& getDerivedRight();
		const CFloat3& getDerivedPosition();
		const CQuaterionF& getDerivedOrientation();
		const CFloat4x4& getDerivedTransform();
	protected:
		Void _update();
	};
}