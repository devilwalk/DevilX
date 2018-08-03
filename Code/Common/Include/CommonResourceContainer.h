#pragma once
#include "CommonType.h"
#include "CommonSTL.h"
namespace NSDevilX
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
	template<class ValueT,class TAllocator=std::allocator<ValueT*> >
	class TResourcePtrVector
		:public TResourcePtrContainer<TVector<ValueT*,TAllocator> >
	{
	public:
		using TResourcePtrContainer<TVector<ValueT*,TAllocator> >::TResourcePtrContainer;
		using TResourcePtrContainer<TVector<ValueT*,TAllocator> >::operator=;
		virtual ~TResourcePtrVector(){}
	};
	template<class ValueT,class TAllocator=std::allocator<ValueT*> >
	class TRefResourcePtrVector
		:public TRefResourcePtrContainer<TVector<ValueT*,TAllocator> >
	{
	public:
		using TRefResourcePtrContainer<TVector<ValueT*,TAllocator> >::TRefResourcePtrContainer;
		using TRefResourcePtrContainer<TVector<ValueT*,TAllocator> >::operator=;
		virtual ~TRefResourcePtrVector()
		{}
	};
	template<class ValueT,class TAllocator=std::allocator<ValueT*> >
	class TCOMResourcePtrVector
		:public TCOMResourcePtrContainer<TVector<ValueT*,TAllocator> >
	{
	public:
		using TCOMResourcePtrContainer<TVector<ValueT*,TAllocator> >::TCOMResourcePtrContainer;
		using TCOMResourcePtrContainer<TVector<ValueT*,TAllocator> >::operator=;
		virtual ~TCOMResourcePtrVector()
		{}
	};
	template<class ValueT,class TAllocator=std::allocator<ValueT*> >
	class TResourcePtrList
		:public TResourcePtrContainer<TList<ValueT*,TAllocator> >
	{
	public:
		using TResourcePtrContainer<TList<ValueT*,TAllocator> >::TResourcePtrContainer;
		using TResourcePtrContainer<TList<ValueT*,TAllocator> >::operator=;
		virtual ~TResourcePtrList(){}
	};
	template<class ValueT,class TSortFunc=std::less<ValueT*>,class TAllocator=std::allocator<ValueT*> >
	class TResourcePtrSet
		:public TResourcePtrContainer<TSet<ValueT*,TSortFunc,TAllocator> >
	{
	public:
		using TResourcePtrContainer<TSet<ValueT*,TSortFunc,TAllocator> >::TResourcePtrContainer;
		using TResourcePtrContainer<TSet<ValueT*,TSortFunc,TAllocator> >::operator=;
		virtual ~TResourcePtrSet()
		{}
	};
	template<class ValueT,class TSortFunc=std::less<ValueT*>,class TAllocator=std::allocator<ValueT*> >
	class TRefResourcePtrSet
		:public TRefResourcePtrContainer<TSet<ValueT*,TSortFunc,TAllocator> >
	{
	public:
		using TRefResourcePtrContainer<TSet<ValueT*,TSortFunc,TAllocator> >::TRefResourcePtrContainer;
		using TRefResourcePtrContainer<TSet<ValueT*,TSortFunc,TAllocator> >::operator=;
		virtual ~TRefResourcePtrSet()
		{}
	};
	template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT>,class TAllocator=std::allocator<std::pair<KeyT,ValueT*> > >
	class TResourcePtrMap
		:public TMap<KeyT,ValueT*,SortfuncT,TAllocator>
	{
	public:
		typedef ValueT ResourceType;
		using TMap<KeyT,ValueT*,SortfuncT,TAllocator>::TMap;
		using TMap<KeyT,ValueT*,SortfuncT,TAllocator>::operator[];
		using TMap<KeyT,ValueT*,SortfuncT,TAllocator>::operator=;
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
	template<typename KeyT,class ValueT,typename SortfuncT=std::less<KeyT>,class TAllocator=std::allocator<std::pair<const KeyT,ValueT*> > >
	class TRefResourcePtrMap
		:public TMap<KeyT,ValueT*,SortfuncT,TAllocator>
	{
	public:
		using TMap<KeyT,ValueT*,SortfuncT,TAllocator>::TMap;
		using TMap<KeyT,ValueT*,SortfuncT,TAllocator>::operator[];
		using TMap<KeyT,ValueT*,SortfuncT,TAllocator>::operator=;
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
	template<class T,class TStringAllocator=std::allocator<Char>,class TAllocator=std::allocator<std::pair<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T*> > >
	class TNamedResourcePtrMap
		:public TResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>
	{
	public:
		using TResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>::TResourcePtrMap;
		using TResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>::operator[];
		using TResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>::operator=;
	};
	template<class T,class TStringAllocator=std::allocator<Char>,class TAllocator=std::allocator<std::pair<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T*> > >
	class TNamedRefResourcePtrMap
		:public TRefResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>
	{
	public:
		using TRefResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>::TRefResourcePtrMap;
		using TRefResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>::operator[];
		using TRefResourcePtrMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,T,std::less<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator>::operator=;
	};
	template<class T,class TStringAllocator=std::allocator<Char>,class TAllocator=std::allocator<T*> >
	class TBaseNamedIndexResourcePtrContainer
	{
	public:
		typedef TMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,SizeT> IndexByNameList;
		typedef TList<T*,TAllocator> ResourcePtrList;
	protected:
		IndexByNameList mIndices;
		ResourcePtrList mResources;
	public:
		TBaseNamedIndexResourcePtrContainer()
		{}
		virtual ~TBaseNamedIndexResourcePtrContainer()
		{
		}
		Void add(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name,T * t)
		{
			if(has(name))
				return;
			mIndices[name]=mResources.size();
			mResources.push_back(t);
		}
		Boolean has(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)const
		{
			return mIndices.has(name);
		}
		SizeT getIndex(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)const
		{
			return mIndices.get(name);
		}
		T * get(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)const
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
		T * remove(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)
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
	template<class T,class TStringAllocator=std::allocator<Char>,class TAllocator=std::allocator<T*> >
	class TNamedIndexResourcePtrContainer
		:public TBaseNamedIndexResourcePtrContainer<T,TStringAllocator,TAllocator>
	{
	public:
		TNamedIndexResourcePtrContainer()
		{}
		virtual ~TNamedIndexResourcePtrContainer()
		{
			destroyAll();
		}
		Void destroy(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)
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
	template<class T,class TStringAllocator=std::allocator<Char>,class TAllocator=std::allocator<T*> >
	class TNamedIndexRefResourcePtrContainer
		:public TBaseNamedIndexResourcePtrContainer<T,TStringAllocator,TAllocator>
	{
	public:
		TNamedIndexRefResourcePtrContainer()
		{}
		virtual ~TNamedIndexRefResourcePtrContainer()
		{
			destroyAll();
		}
		Void destroy(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)
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
