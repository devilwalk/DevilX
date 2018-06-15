#pragma once
#include "STL.h"
#include "IReadWriteLockImp.h"
#include "MemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	namespace NSCore
	{
		template<typename T>
		class TVectorMT
			:public TVector<T>
			,public IReadWriteLockImp
		{
		public:
			using TVector<T>::TVector;
			using TVector<T>::operator=;
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
		template<typename T>
		class TListMT
			:public TList<T>
			,public IReadWriteLockImp
		{
		public:
			using TList<T>::TList;
			using TList<T>::operator=;
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
		template<typename T,typename SortfuncT=std::less<T> >
		class TSetMT
			:public TSet<T,SortfuncT>
			,public IReadWriteLockImp
		{
		public:
			using TSet<T,SortfuncT>::TSet;
			using TSet<T,SortfuncT>::operator=;
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
		template<typename KeyT,typename ValueT,typename SortfuncT=std::less<KeyT> >
		class TMapMT
			:public TMap<KeyT,ValueT,SortfuncT>
			,public IReadWriteLockImp
		{
		public:
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
