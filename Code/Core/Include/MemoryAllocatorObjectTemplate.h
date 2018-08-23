#pragma once
#include "MemoryManager.h"
namespace NSDevilX
{
	namespace NSCore
	{
		template<class T>
		class TMemoryAllocatorObject
		{
		public:
			VoidPtr operator new(SizeT sizeInBytes)
			{
				return CMemoryManager::getSingleton().allocateBytes(sizeInBytes);
			}
			Void operator delete(VoidPtr address)
			{
				CMemoryManager::getSingleton().deallocateBytes(address);
			}
			VoidPtr operator new[](SizeT sizeInBytes);
			Void operator delete[](VoidPtr address);
		};
		template<class T>
		class TBaseObject
			:public TMemoryAllocatorObject<T>
		{
		public:
			using TMemoryAllocatorObject<T>::operator new;
			using TMemoryAllocatorObject<T>::operator delete;
			VoidPtr operator new(SizeT sizeInBytes,ConstCharPtr file,ConstCharPtr function,UInt32 line)
			{
				return CMemoryManager::getSingleton().allocateBytes(sizeInBytes,file,function,line);
			}
			Void operator delete(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
			{
				assert(0);
			}
		};
#define DEVILX_ALLOCATOR_STANDER 0
#define DEVILX_ALLOCATOR_TBB 1
#if DEVILX_DEBUG
#define DEVILX_ALLOCATOR DEVILX_ALLOCATOR_STANDER
#else
#define DEVILX_ALLOCATOR DEVILX_ALLOCATOR_TBB
#endif
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
#define DevilXAllocator std::allocator
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
#define DevilXAllocator tbb::tbb_allocator
#endif
#define DevilXStringAllocator DevilXAllocator<Char>
#define DevilXWStringAllocator DevilXAllocator<WChar>
	}
}
