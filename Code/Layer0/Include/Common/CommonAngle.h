#pragma once
#include "CommonType.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CDegree
		:public TBaseObject<CDegree>
	{
	protected:
		Float mValue;
	public:
		CDegree(Float value=0)
			:mValue(value)
		{}
		operator Float()const
		{
			return mValue;
		}
		Float valueRadian()const
		{
			return mValue/180.0f*DirectX::XM_PI;
		}
	};
	class CRadian
		:public TBaseObject<CRadian>
	{
	protected:
		Float mValue;
	public:
		CRadian(Float value)
			:mValue(value)
		{}
		operator Float()const
		{
			return mValue;
		}
		Float valueDegree()const
		{
			return mValue*DirectX::XM_1DIVPI*180.0f;
		}
	};
}