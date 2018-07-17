#pragma once
#include "Type.h"
#include "STL.h"
#include "STLMT.h"
namespace NSDevilX
{
	namespace NSCore
	{
		template<class ContainerT>
		class TResourcePtrContainer
			:public ContainerT
		{
		public:
			using ContainerT::ContainerT;
			using ContainerT::operator=;
			virtual ~TResourcePtrContainer()
			{
				destroyAll();
			}
			Void destroy(typename ContainerT::value_type value)
			{
				this->remove(value);
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
		template<class ContainerT>
		class TRefResourcePtrContainer
			:public ContainerT
		{
		public:
			using ContainerT::ContainerT;
			using ContainerT::operator=;
			virtual ~TRefResourcePtrContainer()
			{
				destroyAll();
			}
			Void destroy(typename ContainerT::value_type value)
			{
				this->remove(value);
				value->release();
			}
			Void destroyAll()
			{
				for(auto res:*this)
				{
					if(res)
						res->release();
				}
				this->clear();
			}
		};
		template<class ContainerT>
		class TCOMResourcePtrContainer
			:public ContainerT
		{
		public:
			using ContainerT::ContainerT;
			using ContainerT::operator=;
			virtual ~TCOMResourcePtrContainer()
			{
				destroyAll();
			}
			Void destroy(typename ContainerT::value_type value)
			{
				this->remove(value);
				value->Release();
			}
			Void destroyAll()
			{
				for(auto res:*this)
				{
					if(res)
						res->Release();
				}
				this->clear();
			}
		};
		template<class ValueT>
		class TResourcePtrVector
			:public TResourcePtrContainer<TVector<ValueT*> >
		{
		public:
			using TResourcePtrContainer<TVector<ValueT*> >::TResourcePtrContainer;
			using TResourcePtrContainer<TVector<ValueT*> >::operator=;
			virtual ~TResourcePtrVector(){}
		};
		template<class ValueT>
		class TRefResourcePtrVector
			:public TRefResourcePtrContainer<TVector<ValueT*> >
		{
		public:
			using TRefResourcePtrContainer<TVector<ValueT*> >::TRefResourcePtrContainer;
			using TRefResourcePtrContainer<TVector<ValueT*> >::operator=;
			virtual ~TRefResourcePtrVector()
			{}
		};
		template<class ValueT>
		class TCOMResourcePtrVector
			:public TCOMResourcePtrContainer<TVector<ValueT*> >
		{
		public:
			using TCOMResourcePtrContainer<TVector<ValueT*> >::TCOMResourcePtrContainer;
			using TCOMResourcePtrContainer<TVector<ValueT*> >::operator=;
			virtual ~TCOMResourcePtrVector()
			{}
		};
		template<class ValueT>
		class TResourcePtrVectorMT
			:public TResourcePtrContainer<TVectorMT<ValueT*> >
		{
		public:
			using TResourcePtrContainer<TVectorMT<ValueT*> >::TResourcePtrContainer;
			using TResourcePtrContainer<TVectorMT<ValueT*> >::operator=;
			virtual ~TResourcePtrVectorMT()
			{
				destroyAllMT();
			}
			Void destroyMT(ValueT * value)
			{
				eraseMT(value);
				delete value;
			}
			Void destroyAllMT()
			{
				this->lockWrite();
				for(auto res:*this)
				{
					delete res;
				}
				this->clear();
				this->unLockWrite();
			}
		};
		template<class ValueT>
		class TResourcePtrList
			:public TResourcePtrContainer<TList<ValueT*> >
		{
		public:
			using TResourcePtrContainer<TList<ValueT*> >::TResourcePtrContainer;
			using TResourcePtrContainer<TList<ValueT*> >::operator=;
			virtual ~TResourcePtrList(){}
		};
		template<class ValueT>
		class TResourcePtrListMT
			:public TResourcePtrContainer<TListMT<ValueT*> >
		{
		public:
			using TResourcePtrContainer<TListMT<ValueT*> >::TResourcePtrContainer;
			using TResourcePtrContainer<TListMT<ValueT*> >::operator=;
			virtual ~TResourcePtrListMT()
			{
				destroyAllMT();
			}
			Void destroyMT(ValueT * value)
			{
				eraseMT(value);
				delete value;
			}
			Void destroyAllMT()
			{
				this->lockWrite();
				for(auto res:*this)
				{
					delete res;
				}
				this->clear();
				this->unLockWrite();
			}
		};
		template<class ValueT>
		class TResourcePtrSet
			:public TResourcePtrContainer<TSet<ValueT*> >
		{
		public:
			using TResourcePtrContainer<TSet<ValueT*> >::TResourcePtrContainer;
			using TResourcePtrContainer<TSet<ValueT*> >::operator=;
			virtual ~TResourcePtrSet()
			{}
		};
		template<class ValueT>
		class TRefResourcePtrSet
			:public TRefResourcePtrContainer<TSet<ValueT*> >
		{
		public:
			using TRefResourcePtrContainer<TSet<ValueT*> >::TRefResourcePtrContainer;
			using TRefResourcePtrContainer<TSet<ValueT*> >::operator=;
			virtual ~TRefResourcePtrSet()
			{}
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
					if(res)
						res->release();
				}
				this->clear();
				this->unLockWrite();
			}
		};
		template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT> >
		class TResourcePtrMap
			:public TMap<KeyT,ValueT*,SortfuncT>
		{
		public:
			typedef ValueT ResourceType;
			using TMap<KeyT,ValueT*,SortfuncT>::TMap;
			using TMap<KeyT,ValueT*,SortfuncT>::operator[];
			using TMap<KeyT,ValueT*,SortfuncT>::operator=;
			virtual ~TResourcePtrMap()
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
		class TResourcePtrMapMT
			:public TMapMT<KeyT,ValueT*,SortfuncT>
		{
		public:
			typedef ValueT ResourceType;
			virtual ~TResourcePtrMapMT()
			{
				destroyAllMT();
			}
			Void destroy(const KeyT & key)
			{
				auto iter=this->find(key);
				delete iter->second;
				this->erase(iter);
			}
			Void destroyMT(const KeyT & key)
			{
				this->lockWrite();
				destroy(key);
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
				destroyAll();
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
		class TRefResourcePtrMap
			:public TMap<KeyT,ValueT*,SortfuncT>
		{
		public:
			using TMap<KeyT,ValueT*,SortfuncT>::TMap;
			using TMap<KeyT,ValueT*,SortfuncT>::operator[];
			using TMap<KeyT,ValueT*,SortfuncT>::operator=;
			virtual ~TRefResourcePtrMap()
			{
				destroyAll();
			}
			Void destroy(const KeyT & key)
			{
				auto iter=this->find(key);
				iter->second->release();
				this->erase(iter);
			}
			Void destroyAll()
			{
				for(auto res:*this)
				{
					if(res.second)
						res.second->release();
				}
				this->clear();
			}
		};
		template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT> >
		class TRefResourcePtrMapMT
			:public TMapMT<KeyT,ValueT*,SortfuncT>
		{
		public:
			virtual ~TRefResourcePtrMapMT()
			{
				destroyAllMT();
			}
			Void destroy(const KeyT & name)
			{
				auto iter=this->find(key);
				iter->second->release();
				this->erase(iter);
			}
			Void destroyMT(const KeyT & name)
			{
				this->lockWrite();
				destroy(name);
				this->unLockWrite();
			}
			Void destroyAll()
			{
				for(auto res:*this)
				{
					if(res.second)
						res.second->release();
				}
				this->clear();
			}
			Void destroyAllMT()
			{
				this->lockWrite();
				destroyAll();
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
		class TNamedResourcePtrMap
			:public TResourcePtrMap<const String,T>
		{
		public:
			using TResourcePtrMap<const String,T>::TResourcePtrMap;
			using TResourcePtrMap<const String,T>::operator[];
			using TResourcePtrMap<const String,T>::operator=;
		};
		template<class T>
		class TNamedRefResourcePtrMap
			:public TRefResourcePtrMap<const String,T>
		{
		public:
			using TRefResourcePtrMap<const String,T>::TRefResourcePtrMap;
			using TRefResourcePtrMap<const String,T>::operator[];
			using TRefResourcePtrMap<const String,T>::operator=;
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
					if(res)
						res->release();
				}
				this->mResources.clear();
				this->mIndices.clear();
			}
		};
	}
}
