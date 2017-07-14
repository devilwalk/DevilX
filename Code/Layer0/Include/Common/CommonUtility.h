#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonStringConverter.h"
namespace NSDevilX
{
	class CNameGenerator
		:public TBaseObject<CNameGenerator>
	{
	protected:
		String mBaseName;
		UInt32 mIndex;
	public:
		CNameGenerator(const String & baseName)
			:mBaseName(baseName)
			,mIndex(0)
		{}
		~CNameGenerator(){}
		String generateNext()
		{
			return mBaseName+"/"+CStringConverter::toString(mIndex++);
		}
	};
}