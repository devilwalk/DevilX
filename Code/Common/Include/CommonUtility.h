#pragma once
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonStringUtility.h"
namespace NSDevilX
{
	class CNameGenerator
		:public TMemoryAllocatorObject<CNameGenerator>
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

	template<typename T,Bool force=True>
	T convertPointerToNumber(ConstVoidPtr pointer)
	{
		if(force)
			return static_cast<T>(*reinterpret_cast<ConstSizeTPtr>(&pointer));
		else
			return *reinterpret_cast<const T*>(&pointer);
	}
}