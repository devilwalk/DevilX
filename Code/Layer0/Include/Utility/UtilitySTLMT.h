#pragma once
#include "UtilitySTL.h"
#include "UtilityReadWriteLocker.h"
#include "UtilityThreadData.h"
namespace NSDevilX
{
	template<typename T>
	class TVectorMT
		:public DevilXTVector(T)
		,public CReadWriteLocker
	{
	public:
		using DevilXTVector(T)::TVector;
		using DevilXTVector(T)::operator=;
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
		:public DevilXTList(T)
		,public CReadWriteLocker
	{
	public:
		using DevilXTList(T)::TList;
		using DevilXTList(T)::operator=;
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
	template<typename T>
	class TSetMT
		:public DevilXTSet(T)
		,public CReadWriteLocker
	{
	public:
		using DevilXTSet(T)::TSet;
		using DevilXTSet(T)::operator=;
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
	template<typename KeyT,typename ValueT>
	class TMapMT
		:public DevilXTMap(KeyT,ValueT)
		,public CReadWriteLocker
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
	class CPointerQueueMT
		:public TBaseObject<CPointerQueueMT>
	{
	protected:
		VoidPtr mInternalQueue;
	public:
		CPointerQueueMT();
		~CPointerQueueMT();
		template<typename T>
		Void push(T * t)
		{
			_push(t);
		}
		template<typename T>
		T * pop()
		{
			return static_cast<T*>(_pop());
		}
		template<typename T>
		Boolean tryPop(T * & t)
		{
			VoidPtr temp=nullptr;
			Boolean ret=_tryPop(temp);
			t=reinterpret_cast<T*>(temp);
			return ret;
		}
		template<typename T>
		Void getAll(std::vector<T*> & ret)
		{
			ret.clear();
			while(!empty())
			{
				ret.push_back(pop<T>());
			}
			for(auto ele:ret)
				push(ele);
		}
		Void clear();
		Boolean empty();
		SizeT size();
	protected:
		Void _push(VoidPtr data);
		VoidPtr _pop();
		Boolean _tryPop(VoidPtr & data);
	};
	class CUnorderListMT
		:public TBaseObject<CUnorderListMT>
	{
	protected:
		TSharedReadObject<DevilXTVector(TSharedReadData<VoidPtr>*) > mDatas;
	public:
		CUnorderListMT();
		Void pushMT(VoidPtr value);
		VoidPtr tryPopMT();
		VoidPtr popMT();
	};
}
