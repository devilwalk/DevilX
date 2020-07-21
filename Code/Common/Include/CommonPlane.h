#pragma once
#include "CommonMath.h"
namespace NSDevilX
{
	class CPlane
		:public CFloat4
	{
	public:
		using CFloat4::type;

		auto getNormal()const
		{
			return CFloat3(*this);
		}
		auto getD()const
		{
			return w;
		}
		auto distance(const CFloat3& point)const
		{
		}
	};
}