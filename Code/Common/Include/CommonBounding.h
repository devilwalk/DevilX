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
			EIntersect_Contain=(1<<1)|EIntersect_Intersect,
			EIntersect_Contained=(1<<2)|EIntersect_Intersect,
			EIntersect_Unknown=1<<31
		};
	};

	template<class TValue>
	class TBoundingBox
		:public CBoundingVolume
	{
	public:
		typedef TBoundingBox TYPE;
		typedef TValue VALUE_TYPE;
	protected:
		TValue mCenter;
		TValue mExtend;
	public:
		TBoundingBox()
			:mCenter(0)
			,mExtend(0)
		{ }
		TBoundingBox(const TBoundingBox& cpy)
			:mCenter(cpy.mCenter)
			,mExtend(cpy.mExtend)
		{ }
		TBoundingBox(const TValue& center,const TValue& extend)
			:mCenter(center)
			,mExtend(extend)
		{ }
		~TBoundingBox()
		{ }
		auto intersect(const TBoundingBox& bound)const
		{
			auto ret=EIntersect_None;
			auto my_min=min();
			auto my_max=max();
			auto it_min=min();
			auto it_max=max();
			bool my_miner=CMath::allGreaterEqual(it_min,my_min);
			bool my_maxer=CMath::allGreaterEqual(my_max,it_max);
			bool no=CMath::allGreater(my_min,it_max)||CMath::allGreater(it_min,my_max);
			if(no)
			{
				return ret;
			}
			ret=EIntersect_Intersect;
			if(my_miner&&my_maxer)
			{
				ret=EIntersect_Contain;
			}
			else if((!my_miner)&&(!my_maxer))
			{
				ret=EIntersect_Contained;
			}
			return ret;
		}
		auto min()const
		{
			return mCenter-mExtend;
		}
		auto max()const
		{
			return mCenter+mExtend;
		}
	};
	typedef TBoundingBox<CFloat3> CBoundingBox;
	typedef TBoundingBox<CHalf3> CBoundingBoxH;
	typedef TBoundingBox<CInt3> CBoundingBoxI;
	typedef TBoundingBox<CUInt3> CBoundingBoxU;
	typedef TBoundingBox<CFloat2> CBoundingRectF;
	typedef TBoundingBox<CHalf2> CBoundingRectH;
	typedef TBoundingBox<CInt2> CBoundingRectI;
	typedef TBoundingBox<CUInt2> CBoundingRectU;

	class CPlaneBoundedVolume
		:public CBoundingVolume
	{
	public:
		typedef CPlaneBoundedVolume TYPE;
		typedef CPlane VALUE_TYPE;
	protected:
		TVector<CPlane> mPlanes;
	public:
		auto getPlane(UInt32 index)const
		{
			return mPlanes[index];
		}
		auto getPlaneCount()const
		{
			return static_cast<UInt32>(mPlanes.size());
		}
		const auto& getInternal()const
		{
			return mPlanes;
		}
		auto intersect(const CPlaneBoundedVolume& bound)const
		{
			return EIntersect_Unknown;
		}
		auto intersect(const CBoundingBox& bound)const
		{
			for(auto const& plane:mPlanes)
			{

			}
		}
		Boolean contain(const CFloat3& point)const
		{

		}
	};
}