#pragma once
#include "STL.h"
#include "IReadWriteLockImp.h"
#include "MemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	namespace NSCore
	{
		template<typename T,class TAllocator=DevilXAllocator<T> >
		class TVectorMT
			:public TVector<T,TAllocator>
			,public IReadWriteLockImp
		{
		public:
			using TVector<T,TAllocator>::TVector;
			using TVector<T,TAllocator>::operator=;
			Void pushBackMT(T const & t)
			{
				lockWrite();
				this->push_back(t);
				unLockWrite();
			}
			Void popBackMT()
			{
				lockWrite();
				this->pop_back();
				unLockWrite();
			}
		};
		template<typename T,class TAllocator=DevilXAllocator<T> >
		class TListMT
			:public TList<T,TAllocator>
			,public IReadWriteLockImp
		{
		public:
			using TList<T,TAllocator>::TList;
			using TList<T,TAllocator>::operator=;
			Void pushBackMT(T const & t)
			{
				lockWrite();
				this->push_back(t);
				unLockWrite();
			}
			Void popFrontMT()
			{
				lockWrite();
				this->pop_front();
				unLockWrite();
			}
			Void popBackMT()
			{
				lockWrite();
				this->pop_back();
				unLockWrite();
			}
		};
		template<typename T,typename SortfuncT=std::less<T>,class TAllocator=DevilXAllocator<T> >
		class TSetMT
			:public TSet<T,SortfuncT,TAllocator>
			,public IReadWriteLockImp
		{
		public:
			using TSet<T,SortfuncT,TAllocator>::TSet;
			using TSet<T,SortfuncT,TAllocator>::operator=;
			Void insertMT(T const & t)
			{
				lockWrite();
				insert(t);
				unLockWrite();
			}
			Void eraseMT(T const & t)
			{
				lockWrite();
				erase(t);
				unLockWrite();
			}
		};
		template<typename T,typename HashT=std::hash<T>,typename EqualT=std::equal_to<T>,class TAllocator=DevilXAllocator<T> >
		class TUnorderedSetMT
			:public TUnorderedSet<T,HashT,EqualT,TAllocator>
			,public IReadWriteLockImp
		{
		public:
			using TUnorderedSet<T,HashT,EqualT,TAllocator>::TUnorderedSet;
			using TUnorderedSet<T,HashT,EqualT,TAllocator>::operator=;
			Void insertMT(T const & t)
			{
				lockWrite();
				insert(t);
				unLockWrite();
			}
			Void eraseMT(T const & t)
			{
				lockWrite();
				erase(t);
				unLockWrite();
			}
		};
		template<typename KeyT,typename ValueT,typename SortfuncT=std::less<KeyT>,class TAllocator=DevilXAllocator<std::pair<KeyT,ValueT> > >
		class TMapMT
			:public TMap<KeyT,ValueT,SortfuncT,TAllocator>
			,public IReadWriteLockImp
		{
		public:
			using TMap<KeyT,ValueT,SortfuncT,TAllocator>::TMap;
			using TMap<KeyT,ValueT,SortfuncT,TAllocator>::operator=;
			Void addMT(KeyT const & key,ValueT const & value)
			{
				lockWrite();
				add(key,value);
				unLockWrite();
			}
			Void eraseMT(KeyT const & key)
			{
				lockWrite();
				erase(key);
				unLockWrite();
			}
		};
		template<typename KeyT,typename ValueT,typename HashT=std::hash<KeyT>,typename EqualT=std::equal_to<KeyT>,class TAllocator=DevilXAllocator<std::pair<KeyT,ValueT> > >
		class TUnorderedMapMT
			:public TUnorderedMap<KeyT,ValueT,HashT,EqualT,TAllocator>
			,public IReadWriteLockImp
		{
		public:
			using TUnorderedMapMT<KeyT,ValueT,HashT,EqualT,TAllocator>::TUnorderedMapMT;
			using TUnorderedMapMT<KeyT,ValueT,HashT,EqualT,TAllocator>::operator=;
			Void addMT(KeyT const & key,ValueT const & value)
			{
				lockWrite();
				add(key,value);
				unLockWrite();
			}
			Void eraseMT(KeyT const & key)
			{
				lockWrite();
				erase(key);
				unLockWrite();
			}
		};
	}
}
