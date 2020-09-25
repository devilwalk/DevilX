#pragma once
#include "IGDCommandList.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ICommandAllocator
			{
			protected:
				virtual ~ICommandAllocator(){}
			public:
			};
		}
	}
}