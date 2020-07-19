#pragma once
#include "CommonPlane.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	class CBoundingVolume
	{
	public:
		enum EIntersect
		{
			EIntersect_None,
			EIntersect_Intersect=1,
			EIntersect_Contain=(1<<1)|EIntersect_Intersect
		};
	};
	template<class TSelf>
	class TBoundingVolume
		:public CBoundingVolume
	{
	public:
		TBoundingVolume()
		{
		}
		virtual ~TBoundingVolume()
		{
		}

		virtual EIntersect intersect(const TSelf& bound)const=0;
	};

	class CBoundingBox
		:public TBoundingVolume<CBoundingBox>
	{
	protected:
	public:
		virtual EIntersect intersect(const CBoundingBox& bound) const override;
	};

	class CPlaneBoundedVolume
		:public TBoundingVolume<CPlaneBoundedVolume>
	{
	protected:
	public:
		EIntersect intersect(const CBoundingBox& bound)const;

		virtual EIntersect intersect(const CPlaneBoundedVolume& bound) const override;
	};
}