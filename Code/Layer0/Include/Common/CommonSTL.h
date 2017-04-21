#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	template<typename T>
	struct vector
	{
		typedef std::vector<T,TAllocator<T> > type;
	};
	template<typename T>
	struct list
	{
		typedef std::list<T,TAllocator<T> > type;
	};
	template<typename T>
	struct set
	{
		typedef std::set<T,TAllocator<T> > type;
	};
	template<typename KeyT,typename ValueT,typename SortfuncT=std::less<KeyT> >
	struct map
	{
		typedef std::map<KeyT,ValueT,SortfuncT,TAllocator<std::pair<const KeyT,ValueT> > > type;
	};
	typedef std::basic_string<Char,std::char_traits<Char>,TAllocator<Char> > String;
	typedef std::basic_string<WChar,std::char_traits<WChar>,TAllocator<WChar> > WString;
	typedef std::basic_stringstream<Char,std::char_traits<Char>,TAllocator<Char> > StringStream;
	typedef std::basic_stringstream<WChar,std::char_traits<WChar>,TAllocator<WChar> > WStringStream;
#ifdef UNICODE
	typedef WString TString;
	typedef WStringStream TStringStream;
#else
	typedef String TString;
	typedef StringStream TStringStream;
#endif
	template<typename T>
	class TVector
		:public std::vector<T,TAllocator<T> >
		,public TBaseObject<TVector<T> >
	{
	public:
		using std::vector<T,TAllocator<T> >::vector;
		using std::vector<T,TAllocator<T> >::operator[];
		using std::vector<T,TAllocator<T> >::operator=;
		typename std::vector<T,TAllocator<T> >::const_iterator find(T const & t)const
		{
			return std::find(this->begin(),this->end(),t);
		}
		Boolean has(T const & t)const
		{
			return this->find(t)!=this->end();
		}
		Boolean remove(T const & t)
		{
			Boolean ret=false;
			auto iter=this->find(t);
			if(this->end()!=iter)
			{
				this->erase(iter);
				ret=true;
			}
			return ret;
		}
	};
	template<typename T>
	class TList
		:public std::list<T,TAllocator<T> >
		,public TBaseObject<TList<T> >
	{
	public:
		using std::list<T,TAllocator<T> >::list;
		using std::list<T,TAllocator<T> >::operator=;
		const T & operator[](SizeT index)const
		{
			auto iter=this->begin();
			while(index--)
				++iter;
			return *iter;
		}
		T & operator[](SizeT index)
		{
			auto iter=this->begin();
			while(index--)
				++iter;
			return *iter;
		}
		typename std::list<T,TAllocator<T> >::const_iterator find(T const & t)const
		{
			return std::find(this->begin(),this->end(),t);
		}
		Boolean has(T const & t)const
		{
			return this->find(t)!=this->end();
		}
		Boolean remove(T const & t)
		{
			Boolean ret=false;
			auto iter=this->find(t);
			if(this->end()!=iter)
			{
				this->erase(iter);
				ret=true;
			}
			return ret;
		}
	};
	template<typename T,typename SortfuncT=std::less<T> >
	class TSet
		:public std::set<T,SortfuncT,TAllocator<T> >
		,public TBaseObject<TSet<T,SortfuncT> >
	{
	public:
		using std::set<T,SortfuncT,TAllocator<T> >::set;
		using std::set<T,SortfuncT,TAllocator<T> >::operator=;
		Boolean has(T const & t)const
		{
			return this->find(t)!=this->end();
		}
		const T & operator[](SizeT index)const
		{
			auto iter=this->begin();
			while(index--)
				++iter;
			return *iter;
		}
		T & operator[](SizeT index)
		{
			auto iter=this->begin();
			while(index--)
				++iter;
			return *iter;
		}
		Boolean remove(T const & t)
		{
			return 0<this->erase(t);
		}
	};
	template<typename KeyT,typename ValueT,typename SortfuncT=std::less<KeyT> >
	class TMap
		:public std::map<KeyT,ValueT,SortfuncT,TAllocator<std::pair<const KeyT,ValueT> > >
		,public TBaseObject<TMap<KeyT,ValueT,SortfuncT> >
	{
	public:
		using std::map<KeyT,ValueT,SortfuncT,TAllocator<std::pair<const KeyT,ValueT> > >::map;
		using std::map<KeyT,ValueT,SortfuncT,TAllocator<std::pair<const KeyT,ValueT> > >::operator[];
		using std::map<KeyT,ValueT,SortfuncT,TAllocator<std::pair<const KeyT,ValueT> > >::operator=;
		Boolean has(KeyT const & key)const
		{
			return this->find(key)!=this->end();
		}
		ValueT const & get(KeyT const & key)const
		{
			assert(has(key));
			return this->find(key)->second;
		}
		Void add(KeyT const & key,ValueT const & value)
		{
			this->insert(value_type(key,value));
		}
		Boolean remove(ValueT const & t)
		{
			return 0<this->erase(t);
		}
	};
}
