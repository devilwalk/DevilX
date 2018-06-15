#pragma once
#include "CommonType.h"
#include "CommonConstant.h"
#include "CommonMemoryTracker.h"
#include "CommonAllocator.h"
namespace NSDevilX
{
	template<class T>
	class TMemoryAllocatorObject
	{
	public:
		VoidPtr operator new(SizeT sizeInBytes)
		{
			return NSCore::getSystem()->getMemoryManager()->allocateBytes(sizeInBytes);
		}
		Void operator delete(VoidPtr address)
		{
			NSCore::getSystem()->getMemoryManager()->deallocateBytes(address);
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
	extern VoidPtr trackAllocateBytes(SizeT sizeInBytes,ConstCharPtr file,ConstCharPtr function,UInt32 line);
	extern Void trackDeallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line);
	extern VoidPtr trackAlignedAllocateBytes(SizeT sizeInBytes,SizeT alignment,ConstCharPtr file,ConstCharPtr function,UInt32 line);
	extern Void trackAlignedDeallocateBytes(VoidPtr address,ConstCharPtr file,ConstCharPtr function,UInt32 line);
}
