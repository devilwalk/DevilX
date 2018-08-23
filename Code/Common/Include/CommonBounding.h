#pragma once
#include "CommonPlane.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	inline bool operator ==(const DirectX::BoundingBox & leftValue,const DirectX::BoundingBox & rightValue)
	{
		return (leftValue.Center==rightValue.Center)
			&&(leftValue.Extents==rightValue.Extents);
	}
	inline bool operator !=(const DirectX::BoundingBox & leftValue,const DirectX::BoundingBox & rightValue)
	{
		return (leftValue.Center!=rightValue.Center)
			||(leftValue.Extents!=rightValue.Extents);
	}
	extern DirectX::BoundingBox gNullBox;
	class CPlaneBoundedVolume
	{
	public:
		typedef TVector<CPlane> PlaneList;
		PlaneList mPlaneList;
		CPlaneBoundedVolume(){ }
		CPlaneBoundedVolume(const DirectX::BoundingFrustum & frustum)
		{
			*this=frustum;
		}
		~CPlaneBoundedVolume(){}
		const CPlaneBoundedVolume & operator=(const DirectX::BoundingFrustum & frustum)
		{
			mPlaneList.reserve(6);
			merge(frustum);
		}
		Boolean operator==(const CPlaneBoundedVolume & bound)const
		{
			if(mPlaneList.size()!=bound.mPlaneList.size())
				return false;
			for(decltype(mPlaneList.size()) i=0;i<mPlaneList.size();++i)
			{
				if(mPlaneList[i]!=bound.mPlaneList[i])
					return false;
			}
			return true;
		}
		void merge(const DirectX::BoundingFrustum & frustum)
		{
			DirectX::XMVECTOR planes[6];
			frustum.GetPlanes(&planes[0],&planes[1],&planes[2],&planes[3],&planes[4],&planes[5]);
			for(int i=0;i<6;++i)
				mPlaneList.push_back(planes[i]);
		}
		DirectX::ContainmentType contains(const CFloat3 & point)const
		{
			DirectX::ContainmentType ret=DirectX::CONTAINS;
			for(size_t i=0,count=mPlaneList.size();i<count;++i)
			{
				const CPlane & plane=mPlaneList[i];
				DirectX::ContainmentType ct=PlaneTestPoint3D(plane,point);
				switch(ct)
				{
				case DirectX::DISJOINT:
					return DirectX::DISJOINT;
				case DirectX::INTERSECTS:
					return DirectX::INTERSECTS;
				}
			}
			return ret;
		}
		template<class boundsT>
		DirectX::ContainmentType contains(const boundsT & bounds)const
		{
			DirectX::ContainmentType ret=DirectX::CONTAINS;
			for(size_t i=0,count=mPlaneList.size();i<count;++i)
			{
				const CPlane & plane=mPlaneList[i];
				DirectX::PlaneIntersectionType pit=bounds.Intersects(plane);
				switch(pit)
				{
				case DirectX::BACK:
					return DirectX::DISJOINT;
				case DirectX::INTERSECTING:
					ret=DirectX::INTERSECTS;
				}
			}
			return ret;
		}
	};
}