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
			void * allocateBytes(size_t sizeInBytes);
			void deallocateBytes(void * address);
			void * alignedAllocateBytes(size_t sizeInBytes,size_t alignment);
			void alignedDeallocateBytes(void * address);
		};
	}
}