#pragma once
#include "CommonDefine.h"
#include "CommonType.h"
namespace NSDevilX
{
	class CAny
		:public boost::any
		,public TMemoryAllocatorObject<CAny>
	{
	public:
		using boost::any::any;
	};
}
