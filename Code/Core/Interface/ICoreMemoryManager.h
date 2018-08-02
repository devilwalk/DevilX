#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI IMemoryManager
		{
		protected:
			~IMemoryManager();
		public:
			void * allocateBytes(SizeT sizeInBytes);
			void deallocateBytes(VoidPtr address);
			void * alignedAllocateBytes(SizeT sizeInBytes,SizeT alignment);
			void alignedDeallocateBytes(VoidPtr address);
		};
	}
}