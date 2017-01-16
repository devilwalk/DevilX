#pragma once
#include "CommonVectorF.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CRay
		:public TBaseObject<CRay>
	{
	protected:
		CFloat3 mOrigin;
		CFloat3 mDirection;
	public:
		CRay(){}
		CRay(DirectX::FXMVECTOR origin,DirectX::FXMVECTOR direction)
		{
			setParameter(origin,direction);
		}
		~CRay(){}
		Void setParameter(DirectX::FXMVECTOR origin,DirectX::FXMVECTOR direction)
		{
			mOrigin=origin;
			mDirection=direction;
		}
		const CFloat3 & getOrigin()const
		{
			return mOrigin;
		}
		const CFloat3 & getDirection()const
		{
			return mDirection;
		}
	};
}