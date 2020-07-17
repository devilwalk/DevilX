#pragma once
#include "CommonType.h"
namespace NSDevilX
{
	class CRadian;
	class CDegree
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
		operator CRadian()const;
		Float valueRadian()const
		{
			return mValue/180.0f*3.1415926f;
		}
	};
	class CRadian
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
		operator CDegree()const;
		Float valueDegree()const
		{
			return mValue*180.0f/3.1415926f;
		}
	};
}