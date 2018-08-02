#pragma once
#include "CommonType.h"
namespace NSDevilX
{
	template<typename T>
	T clamp(T value,T minValue,T maxValue)
	{
		return (value<minValue)?minValue:((value>maxValue)?maxValue:value);
	}

	inline Float saturate(Float value)
	{
		return clamp(value,0.0f,1.0f);
	}
}