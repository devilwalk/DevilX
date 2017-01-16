#include "Precompiler.h"
using namespace NSDevilX;

Void NSDevilX::CStringUtility::split(const String & text,const String & splitKey,TVector<String> & ret)
{
	auto copy=text;
	while(String::npos!=copy.find(splitKey))
	{
		ret.push_back(copy.substr(0,copy.find_first_of(splitKey)));
		copy=copy.substr(copy.find_first_of(splitKey)+1);
	}
	ret.push_back(copy);
}
