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
				VoidPtr ret=operator new(sizeInBytes);
				getDefaultMemoryTracker()->allocate(ret,sizeInBytes,file,function,line);
				return ret;
			}
			Void operator delete(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line)
			{
				operator delete(address);
			}
		};
#define DEVILX_ALLOCATOR_STANDER 0
#define DEVILX_ALLOCATOR_TBB 1
#define DEVILX_ALLOCATOR DEVILX_ALLOCATOR_TBB
#if DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_STANDER
#define DevilXAllocator std::allocator
#elif DEVILX_ALLOCATOR==DEVILX_ALLOCATOR_TBB
#define DevilXAllocator tbb::tbb_allocator
#endif
#define DevilXStringAllocator DevilXAllocator<Char>
#define DevilXWStringAllocator DevilXAllocator<WChar>
	}
}
