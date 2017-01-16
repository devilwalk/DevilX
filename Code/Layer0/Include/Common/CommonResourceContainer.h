#pragma once
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonSTLMT.h"
namespace NSDevilX
{
	template<class ValueT>
	class TResourcePtrSet
		:public TSet<ValueT*>
	{
	public:
		using TSet<ValueT*>::TSet;
		using TSet<ValueT*>::operator=;
		virtual ~TResourcePtrSet()
		{
			destroyAll();
		}
		Void destroy(ValueT * value)
		{
			this->erase(value);
			delete value;
		}
		Void destroyAll()
		{
			for(auto res:*this)
			{
				delete res;
			}
			this->clear();
		}
	};
	template<class ValueT>
	class TRefResourcePtrSet
		:public TSet<ValueT*>
	{
	public:
		using TSet<ValueT*>::TSet;
		using TSet<ValueT*>::operator=;
		virtual ~TRefResourcePtrSet()
		{
			destroyAll();
		}
		Void destroy(ValueT * value)
		{
			this->erase(value);
			value->release();
		}
		Void destroyAll()
		{
			for(auto res:*this)
			{
				res->release();
			}
			this->clear();
		}
	};
	template<class ValueT>
	class TRefResourcePtrSetMT
		:public TSetMT<ValueT*>
	{
	public:
		virtual ~TRefResourcePtrSetMT()
		{
			destroyAllMT();
		}
		Void destroy(ValueT * value)
		{
			this->erase(value);
			value->release();
		}
		Void destroyMT(ValueT * value)
		{
			eraseMT(value);
			value->release();
		}
		Void destroyAllMT()
		{
			this->lockWrite();
			for(auto res:*this)
			{
				res->release();
			}
			this->clear();
			this->unLockWrite();
		}
	};
	template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT> >
	class TResourcePtrContainer
		:public TMap<KeyT,ValueT*,SortfuncT>
	{
	public:
		typedef ValueT ResourceType;
		using TMap<KeyT,ValueT*,SortfuncT>::TMap;
		using TMap<KeyT,ValueT*,SortfuncT>::operator[];
		using TMap<KeyT,ValueT*,SortfuncT>::operator=;
		virtual ~TResourcePtrContainer()
		{
			destroyAll();
		}
		Void destroy(const KeyT & key)
		{
			auto iter=this->find(key);
			delete iter->second;
			this->erase(iter);
		}
		Void destroyAll()
		{
			for(auto res:*this)
			{
				delete res.second;
			}
			this->clear();
		}
		ValueT * get(KeyT const & key)const
		{
			auto iter=this->find(key);
			if(this->end()==iter)
				return nullptr;
			else
				return iter->second;
		}
	};
	template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT> >
	class TResourcePtrContainerMT
		:public TMapMT<KeyT,ValueT*,SortfuncT>
	{
	public:
		typedef ValueT ResourceType;
		virtual ~TResourcePtrContainerMT()
		{
			destroyAllMT();
		}
		Void destroy(const KeyT & key)
		{
			delete get(key);
			this->erase(key);
		}
		Void destroyMT(const KeyT & key)
		{
			this->lockWrite();
			delete get(key);
			this->erase(key);
			this->unLockWrite();
		}
		Void destroyAll()
		{
			for(auto res:*this)
			{
				delete res.second;
			}
			this->clear();
		}
		Void destroyAllMT()
		{
			this->lockWrite();
			for(auto res:*this)
			{
				delete res.second;
			}
			this->clear();
			this->unLockWrite();
		}
		ValueT * get(KeyT const & key)const
		{
			auto iter=this->find(key);
			if(this->end()==iter)
				return nullptr;
			else
				return iter->second;
		}
		ValueT * getMT(KeyT const & key)const
		{
			this->lockRead();
			auto iter=this->find(key);
			this->unLockRead();
			if(this->end()==iter)
				return nullptr;
			else
				return iter->second;
		}
	};
	template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT> >
	class TRefResourcePtrContainer
		:public TMap<KeyT,ValueT*,SortfuncT>
	{
	public:
		using TMap<KeyT,ValueT*,SortfuncT>::TMap;
		using TMap<KeyT,ValueT*,SortfuncT>::operator[];
		using TMap<KeyT,ValueT*,SortfuncT>::operator=;
		virtual ~TRefResourcePtrContainer()
		{
			destroyAll();
		}
		Void destroy(const KeyT & name)
		{
			((*this)[name])->release();
			this->erase(name);
		}
		Void destroyAll()
		{
			for(auto res:*this)
			{
				res.second->release();
			}
			this->clear();
		}
	};
	template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT> >
	class TRefResourcePtrContainerMT
		:public TMapMT<KeyT,ValueT*,SortfuncT>
	{
	public:
		virtual ~TRefResourcePtrContainerMT()
		{
			destroyAllMT();
		}
		Void destroy(const KeyT & name)
		{
			get(name)->release();
			this->erase(name);
		}
		Void destroyMT(const KeyT & name)
		{
			this->lockWrite();
			get(name)->release();
			this->erase(name);
			this->unLockWrite();
		}
		Void destroyAll()
		{
			for(auto res:*this)
			{
				res.second->release();
			}
			this->clear();
		}
		Void destroyAllMT()
		{
			this->lockWrite();
			for(auto res:*this)
			{
				res.second->release();
			}
			this->clear();
			this->unLockWrite();
		}
		ValueT * get(KeyT const & key)const
		{
			auto iter=this->find(key);
			if(this->end()==iter)
				return nullptr;
			else
				return iter->second;
		}
		ValueT * getMT(KeyT const & key)const
		{
			this->lockRead();
			auto iter=this->find(key);
			this->unLockRead();
			if(this->end()==iter)
				return nullptr;
			else
				return iter->second;
		}
	};
	template<class T>
	class TNamedResourcePtrContainer
		:public TResourcePtrContainer<const String,T>
	{
	public:
		using TResourcePtrContainer<const String,T>::TResourcePtrContainer;
		using TResourcePtrContainer<const String,T>::operator[];
		using TResourcePtrContainer<const String,T>::operator=;
	};
	template<class T>
	class TNamedRefResourcePtrContainer
		:public TRefResourcePtrContainer<const String,T>
	{
	public:
		using TRefResourcePtrContainer<const String,T>::TRefResourcePtrContainer;
		using TRefResourcePtrContainer<const String,T>::operator[];
		using TRefResourcePtrContainer<const String,T>::operator=;
	};
	template<class T>
	class TBaseNamedIndexResourcePtrContainer
	{
	public:
		typedef TMap<const String,SizeT> IndexByNameList;
		typedef TList<T*> ResourcePtrList;
	protected:
		IndexByNameList mIndices;
		ResourcePtrList mResources;
	public:
		TBaseNamedIndexResourcePtrContainer()
		{}
		virtual ~TBaseNamedIndexResourcePtrContainer()
		{
		}
		Void add(const String & name,T * t)
		{
			if(has(name))
				return;
			mIndices[name]=mResources.size();
			mResources.push_back(t);
		}
		Boolean has(const String & name)const
		{
			return mIndices.has(name);
		}
		SizeT getIndex(const String & name)const
		{
			return mIndices.get(name);
		}
		T * get(const String & name)const
		{
			if(!has(name))
				return nullptr;
			SizeT index=mIndices.get(name);
			typename ResourcePtrList::const_iterator iter=_getIterator(index);
			T * ret=*iter;
			return ret;
		}
		T * get(SizeT index)const
		{
			if(mResources.size()<=index)
				return nullptr;
			typename ResourcePtrList::const_iterator iter=_getIterator(index);
			T * ret=*iter;
			return ret;
		}
		T * remove(const String & name)
		{
			if(!has(name))
				return 0;
			SizeT index=mIndices.get(name);
			typename ResourcePtrList::const_iterator iter=_getIterator(index);
			T * ret=*iter;
			mResources.erase(iter);
			mIndices.erase(name);
			return ret;
		}
		SizeT size()const
		{
			return mResources.size();
		}
		Void clear()
		{
			mResources.clear();
			mIndices.clear();
		}
	protected:
		typename ResourcePtrList::const_iterator _getIterator(SizeT index)const
		{
			typename ResourcePtrList::const_iterator ret=mResources.begin();
			while(index--)
			{
				++ret;
			}
			return ret;
		}
	};
	template<class T>
	class TNamedIndexResourcePtrContainer
		:public TBaseNamedIndexResourcePtrContainer<T>
	{
	public:
		TNamedIndexResourcePtrContainer()
		{}
		virtual ~TNamedIndexResourcePtrContainer()
		{
			destroyAll();
		}
		Void destroy(const String & name)
		{
			delete this->remove(name);
		}
		Void destroyAll()
		{
			for(auto res:this->mResources)
			{
				delete res;
			}
			this->mResources.clear();
			this->mIndices.clear();
		}
	};
	template<class T>
	class TNamedIndexRefResourcePtrContainer
		:public TBaseNamedIndexResourcePtrContainer<T>
	{
	public:
		TNamedIndexRefResourcePtrContainer()
		{}
		virtual ~TNamedIndexRefResourcePtrContainer()
		{
			destroyAll();
		}
		Void destroy(const String & name)
		{
			this->remove(name)->release();
		}
		Void destroyAll()
		{
			for(auto res:this->mResources)
			{
				res->release();
			}
			this->mResources.clear();
			this->mIndices.clear();
		}
	};
}
