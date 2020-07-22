#pragma once
#include "CommonMath.h"
namespace NSDevilX
{
	class CPlane
	{
	public:
		enum EFaceForward
		{
			EFaceForward_Back=-1,
			EFaceForward_Intersect=0,
			EFaceForward_Front=1,
		};
	protected:
		CFloat3 mNormal;
		Float mD;
	public:
		CPlane()
			:mNormal(CMath::sUnitY)
			,mD(0)
		{ }
		~CPlane(){ }
		auto& getNormal()const
		{
			return mNormal;
		}
		auto getD()const
		{
			return mD;
		}
		operator CFloat4()
		{
			return CFloat4(mNormal,mD);
		}
		auto distance(const CFloat3& point)const
		{
			return CMath::dot(mNormal,point)+mD;
		}
		auto faceForward(const CFloat3& point,Float epsilon=1e-8f)const
		{
			auto dist=distance(point);
			if(dist>epsilon)
			{
				return EFaceForward_Front;
			}
			else if(dist<-epsilon)
			{
				return EFaceForward_Back;
			}
			else
			{
				return EFaceForward_Intersect;
			}
		}
	};
}