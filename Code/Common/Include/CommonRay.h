#pragma once
#include "CommonMath.h"
namespace NSDevilX
{
	class CRay
		:public TMemoryAllocatorObject<CRay>
	{
	protected:
		CFloat3 mOrigin;
		CFloat3 mDirection;
	public:
		CRay(){}
		CRay(const CFloat3 & origin,const CFloat3 & direction)
		{
			setParameter(origin,direction);
		}
		~CRay(){}
		Void setParameter(const CFloat3 & origin,const CFloat3 & direction)
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