#pragma once
#include "CommonSTL.h"
namespace NSDevilX
{
	class CStringUtility
	{
	public:
		static Void split(const String & text,const String & splitKey,TVector<String> & ret);
	};
}