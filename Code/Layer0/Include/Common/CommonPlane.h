#pragma once
#include "CommonVectorF.h"
namespace NSDevilX
{
	class CPlane
		:public CFloat4
	{
	public:
		using CFloat4::CFloat4;
		using CFloat4::operator DirectX::XMVECTOR;
		using CFloat4::operator=;
		const CFloat3 & getNormal()const
		{
			return *reinterpret_cast<const CFloat3*>(this);
		}
		Float getD()const
		{
			return w;
		}
		DirectX::XMVECTOR normalizeCopy()const
		{
			return DirectX::XMPlaneNormalize(*this);
		}
		Void normalize()
		{
			*this=normalizeCopy();
		}
	};
	inline DirectX::ContainmentType XM_CALLCONV PlaneTestPoint3D(DirectX::FXMVECTOR plane3D,DirectX::FXMVECTOR point3D)
	{
		Float dot_value;
		DirectX::XMStoreFloat(&dot_value,DirectX::XMPlaneDotCoord(plane3D,point3D));
		if(dot_value>0.0f)
			return DirectX::CONTAINS;
		else if(dot_value<0.0f)
			return DirectX::DISJOINT;
		else if(dot_value==0.0f)
			return DirectX::INTERSECTS;
	}
}