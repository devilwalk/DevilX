#pragma once
#include "CommonPlane.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	template<class TSelf>
	class TBoundingVolume
	{
	public:
		enum EIntersect
		{
			EIntersect_None,
			EIntersect_Intersect=1,
			EIntersect_Contain=(1<<1)|EIntersect_Intersect
		};
	public:
		TBoundingVolume()
		{
		}
		virtual ~TBoundingVolume()
		{
		}

		virtual EIntersect intersect(const TBoundingVolume& bound)=0;
	};

	class CBoundingBox
		:public TBoundingVolume<CBoundingBox>
	{
	protected:
	public:
	};

	class CPlaneBoundedVolume
		:public TBoundingVolume<CPlaneBoundedVolume>
	{
	protected:
	public:
		EIntersect intersect(const CBoundingBox& bound);
	};
}