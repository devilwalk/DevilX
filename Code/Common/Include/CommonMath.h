#pragma once
#include "CommonType.h"
namespace NSDevilX
{
	template<typename T>
	auto clampT(T value,T minValue,T maxValue)
	{
		return (value<minValue)?minValue:((value>maxValue)?maxValue:value);
	}

	inline Float saturate(Float value)
	{
		return clampT(value,0.0f,1.0f);
	}
}