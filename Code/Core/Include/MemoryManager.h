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
			VoidPtr allocateBytes(SizeT sizeInBytes,UInt32 blockType=0,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr);
			Void deallocateBytes(VoidPtr address,UInt32 blockType=0,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr);
			VoidPtr alignedAllocateBytes(SizeT sizeInBytes,SizeT alignment,UInt32 blockType=0,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr);
			Void alignedDeallocateBytes(VoidPtr address,UInt32 blockType=0,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr);
			template<typename T>
			T * newNormal(UInt32 blockType=0,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr)
			{
				auto ret=static_cast<T*>(allocateBytes(sizeof(T),blockType,file,line,function));
				return ret;
			}
			template<class T>
			T * newObject(UInt32 blockType=0,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr)
			{
				auto ret=newNormal<T>();
				ret->T::T();
				return ret;
			}
			template<class T>
			Void deleteObject(T * pointer,UInt32 blockType=0,ConstCharPtr file=nullptr,UInt32 line=0,ConstCharPtr function=nullptr)
			{
				pointer->T::~T();
				deallocateBytes(pointer,blockType,file,line,function);
			}
		};
	}
}