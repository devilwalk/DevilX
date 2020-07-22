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
		TValue mMin;
		TValue mMax;
	public:
		TBoundingBox()
			:mMin(0)
			,mMax(0)
		{ }
		TBoundingBox(const TBoundingBox& cpy)
			:mMin(cpy.mMin)
			,mMax(cpy.mMax)
		{ }
		TBoundingBox(const TValue& minPt,const TValue& maxPt)
			:mMin(minPt)
			,mMax(maxPt)
		{ }
		~TBoundingBox()
		{ }
		auto intersect(const TBoundingBox& bound)const
		{
			auto ret=EIntersect_None;
			auto& my_min=min();
			auto& my_max=max();
			auto& it_min=bound.min();
			auto& it_max=bound.max();
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
		auto& min()const
		{
			return mMin;
		}
		auto& max()const
		{
			return mMax;
		}
		auto center()const
		{
			auto& min_pt=min();
			auto& max_pt=max();
			return min_pt+(max_pt-min_pt)*0.5f;
		}
		auto extend()const
		{
			auto& min_pt=min();
			auto& max_pt=max();
			return max_pt-min_pt;
		}
		void corners(OUT TVector<TValue>& oCorners)const
		{
			static const TValue corner_extends[]=
			{
				TValue(0,0,0),
				TValue(1,0,0),
				TValue(0,1,0),
				TValue(0,0,1),
				TValue(1,1,0),
				TValue(1,0,1),
				TValue(0,1,1),
				TValue(1,1,1),
			};
			auto& min_pt=min();
			auto ext=extend();
			oCorners.resize(8);
			for(UInt32 i=0;i<8;++i)
			{
				oCorners[i]=min_pt+ext*corner_extends[i];
			}
		}
		auto corners()const
		{
			TVector<TValue> ret;
			corners(ret);
			return ret;
		}
	};
	typedef TBoundingBox<CFloat3> CBoundingBox;
	typedef TBoundingBox<CHalf3> CBoundingBoxH;
	typedef TBoundingBox<CInt3> CBoundingBoxI;
	typedef TBoundingBox<CUInt3> CBoundingBoxU;

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
			TVector<CBoundingBox::VALUE_TYPE> ret;
			bound.corners(ret);
			CBoolean4 contains[]={CBoolean4(false),CBoolean4(false)};
			for(int i=0;i<8;++i)
			{
				contains[i/4][i%4]=contain(ret[i]);
			}
			if(CMath::all(contains[0])&&CMath::all(contains[1]))
			{
				return EIntersect_Contain;
			}
			if(CMath::any(contains[0])||CMath::any(contains[1]))
			{
				return EIntersect_Intersect;
			}
			return EIntersect_None;
		}
		Boolean contain(const CFloat3& point)const
		{
			auto ret=true;
			for(auto const& plane:mPlanes)
			{
				ret&=(plane.faceForward(point)>=0);
			}
			return ret;
		}
	};
}