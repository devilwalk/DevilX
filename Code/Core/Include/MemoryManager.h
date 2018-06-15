#pragma once
#include "Singleton.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CMemoryManager
			:public TSingletonEx<CMemoryManager>
		{
		public:
			VoidPtr allocateBytes(SizeT sizeInBytes);
			Void deallocateBytes(VoidPtr address);
			VoidPtr alignedAllocateBytes(SizeT sizeInBytes,SizeT alignment);
			Void alignedDeallocateBytes(VoidPtr address);
		};
	}
}