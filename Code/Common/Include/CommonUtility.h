#pragma once
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonStringUtility.h"
namespace NSDevilX
{
	class CNameGenerator
	{
	protected:
		std::string mBaseName;
		UInt32 mIndex;
	public:
		CNameGenerator(ConstCharPtr baseName)
			:mBaseName(baseName)
			,mIndex(0)
		{}
		~CNameGenerator(){}
		ConstCharPtr generateNext()
		{
			return (mBaseName+"/"+CStringUtility::toString(mIndex++)).c_str();
		}
	};
}