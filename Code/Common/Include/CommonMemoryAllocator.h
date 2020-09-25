#pragma once
#include "CommonMemoryTracer.h"
namespace NSDevilX
{
	class CMemoryAllocator
	{
	public:
		static CMemoryAllocator* sDefault;
	public:
		virtual VoidPtr malloc(SizeT sizeInBytes)
		{
			return ::operator new(sizeInBytes);
		}
		virtual Void free(VoidPtr address)
		{
			::operator delete(address);
		}
	};

	template<typename T>
	class TMemoryAllocator
		:public CMemoryAllocator
		,public std::allocator<T>
	{
	public:
		using std::allocator<T>::allocator;
	};

	class CTBBMemoryAllocator
		:public CMemoryAllocator
	{
	public:
		virtual VoidPtr malloc(SizeT sizeInBytes)
		{
			return scalable_malloc(sizeInBytes);
		}
		virtual Void free(VoidPtr address)
		{
			scalable_free(address);
		}
	};

	template<typename T>
	class TTBBMemoryAllocator
		:public CTBBMemoryAllocator
		,public tbb::scalable_allocator<T>
	{
	public:
		using tbb::scalable_allocator<T>::scalable_allocator;
	};

	template<typename T>
	class TMemoryAllocatorObject
	{
	protected:
		CMemoryAllocator* mMemoryAllocator;
	public:
		VoidPtr operator new(SizeT sizeInBytes,CMemoryAllocator* allocator=CMemoryAllocator::sDefault)
		{
			auto ret=allocator->malloc(sizeInBytes);
			static_cast<TMemoryAllocatorObject<T>*>(static_cast<T*>(ret))->mMemoryAllocator=allocator;
			return ret;
		}
		VoidPtr operator new(SizeT sizeInBytes,ConstCharPtr fileName,UInt32 lineNumber,ConstCharPtr functionName,CMemoryAllocator* allocator=CMemoryAllocator::sDefault)
		{
			auto ret=operator new(sizeInBytes,allocator);
			CMemoryTracer::sInstance.allocate(ret,sizeInBytes,fileName,functionName,lineNumber);
			return ret;
		}
		Void operator delete(VoidPtr address)
		{
			CMemoryTracer::sInstance.deallocate(address);
			static_cast<TMemoryAllocatorObject<T>*>(static_cast<T*>(address))->mMemoryAllocator->free(address);
		}
		Void operator delete(VoidPtr address,CMemoryAllocator* allocator)
		{
			assert(false);
		}
		Void operator delete(VoidPtr address,ConstCharPtr,UInt32,ConstCharPtr,CMemoryAllocator*)
		{
			assert(false);
		}
	};
}