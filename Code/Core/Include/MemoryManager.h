#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CMemoryTracker;
		class CMemoryManager
			:public TSingletonEx<CMemoryManager>
		{
		protected:
#ifdef DEVILX_MEMORY_TRACK_ENABLE
			CMemoryTracker * mMemoryTracker;
#endif
		public:
			CMemoryManager();
			~CMemoryManager();
#ifdef DEVILX_MEMORY_TRACK_ENABLE
			CMemoryTracker * getMemoryTracker()
			{
				return mMemoryTracker;
			}
#endif
			VoidPtr allocateBytes(SizeT sizeInBytes,ConstCharPtr file=nullptr,ConstCharPtr function=nullptr,UInt32 line=0);
			Void deallocateBytes(VoidPtr address,ConstCharPtr file=nullptr,ConstCharPtr function=nullptr,UInt32 line=0);
			VoidPtr alignedAllocateBytes(SizeT sizeInBytes,SizeT alignment,ConstCharPtr file=nullptr,ConstCharPtr function=nullptr,UInt32 line=0);
			Void alignedDeallocateBytes(VoidPtr address,ConstCharPtr file=nullptr,ConstCharPtr function=nullptr,UInt32 line=0);
			template<typename T>
			T * newNormal(ConstCharPtr file=nullptr,ConstCharPtr function=nullptr,UInt32 line=0)
			{
				auto ret=static_cast<T*>(allocateBytes(sizeof(T),file,function,line));
				return ret;
			}
			template<class T>
			T * newObject(ConstCharPtr file=nullptr,ConstCharPtr function=nullptr,UInt32 line=0)
			{
				auto ret=newNormal<T>();
				ret->T::T();
				return ret;
			}
			template<class T>
			Void deleteObject(T * pointer,ConstCharPtr file=nullptr,ConstCharPtr function=nullptr,UInt32 line=0)
			{
				pointer->T::~T();
				deallocateBytes(pointer,file,function,line);
			}
		};
	}
}