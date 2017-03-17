#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonType.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	class CFileName
		:public TBaseObject<CFileName>
	{
	protected:
		String mValue;
	public:
		CFileName(const String & value)
			:mValue(value)
		{}
		~CFileName(){}
		operator String&()
		{
			return mValue;
		}
		String getExt()const
		{
		}
	};
}