#pragma once
#include "CommonGroup.h"
#include "CommonMemoryAllocator.h"
namespace NSDevilX
{
	template<typename T,class TAllocator=TDevilXAllocator<T> >
	class TVector
		:public std::vector<T,TAllocator>
		,public TMemoryAllocatorObject<TVector<T,TAllocator> >
	{
	public:
		using std::vector<T,TAllocator>::vector;
		using std::vector<T,TAllocator>::operator[];
		using std::vector<T,TAllocator>::operator=;
		TVector()
		{}
		template<class TAllocator2>
		TVector(const std::vector<T,TAllocator2> & cpy)
			:std::vector<T,TAllocator>(cpy.begin(),cpy.end())
		{}
		template<class TAllocator2>
		operator std::vector<T,TAllocator2>()const
		{
			return std::vector<T,TAllocator2>(this->begin(),this->end());
		}
		typename std::vector<T,TAllocator>::const_iterator find(T const & t)const
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
		template<typename T2>
		T2 sizeT()const{ return static_cast<T2>(this->size()); }
	};
	template<typename T,class TAllocator=TDevilXAllocator<T> >
	class TList
		:public std::list<T,TAllocator>
		,public TMemoryAllocatorObject<TList<T,TAllocator> >
	{
	public:
		using std::list<T,TAllocator>::list;
		using std::list<T,TAllocator>::operator=;
		TList(){}
		template<class TAllocator2>
		TList(const std::list<T,TAllocator2> & cpy)
			:std::list<T,TAllocator>(cpy.begin(),cpy.end())
		{}
		template<class TAllocator2>
		operator std::list<T,TAllocator2>()const
		{
			return std::list<T,TAllocator2>(this->begin(),this->end());
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
		typename std::list<T,TAllocator>::const_iterator find(T const & t)const
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
	template<typename T,class SortfuncT=std::less<T>,class TAllocator=TDevilXAllocator<T> >
	class TSet
		:public std::set<T,SortfuncT,TAllocator>
		,public TMemoryAllocatorObject<TSet<T,SortfuncT,TAllocator> >
	{
	public:
		using std::set<T,SortfuncT,TAllocator>::set;
		using std::set<T,SortfuncT,TAllocator>::operator=;
		TSet() {}
		template<class TAllocator2>
		TSet(const std::set<T,SortfuncT,TAllocator2> & cpy)
			:std::set<T,SortfuncT,TAllocator>(cpy.begin(),cpy.end())
		{}
		template<class TAllocator2>
		operator std::set<T,SortfuncT,TAllocator2>()const
		{
			return std::set<T,SortfuncT,TAllocator2>(this->begin(),this->end());
		}
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
	template<typename T,class HashT=std::hash<T>,
		class KeyEqualT=std::equal_to<T>
		,class TAllocator=TDevilXAllocator<T> >
		class TUnorderedSet
		:public std::unordered_set<T,HashT,KeyEqualT,TAllocator>
		,public TMemoryAllocatorObject<TUnorderedSet<T,HashT,KeyEqualT,TAllocator> >
	{
	public:
		using std::unordered_set<T,HashT,KeyEqualT,TAllocator>::unordered_set;
		using std::unordered_set<T,HashT,KeyEqualT,TAllocator>::operator=;
		TUnorderedSet()
		{
		}
		template<class TAllocator2>
		TUnorderedSet(const std::unordered_set<T,HashT,KeyEqualT,TAllocator2> & cpy)
			:std::unordered_set<T,HashT,KeyEqualT,TAllocator>(cpy.begin(),cpy.end())
		{
		}
		template<class TAllocator2>
		operator std::unordered_set<T,HashT,KeyEqualT,TAllocator2>()const
		{
			return std::unordered_set<T,HashT,KeyEqualT,TAllocator2>(this->begin(),this->end());
		}
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
	template<typename KeyT,typename ValueT,class SortfuncT=std::less<KeyT>,class TAllocator=TDevilXAllocator<std::pair<const KeyT,ValueT> > >
	class TMap
		:public std::map<KeyT,ValueT,SortfuncT,TAllocator>
		,public TMemoryAllocatorObject<TMap<KeyT,ValueT,SortfuncT,TAllocator> >
	{
	public:
		using std::map<KeyT,ValueT,SortfuncT,TAllocator>::map;
		using std::map<KeyT,ValueT,SortfuncT,TAllocator>::operator[];
		using std::map<KeyT,ValueT,SortfuncT,TAllocator>::operator=;

		using _Mybase=std::map<KeyT,ValueT,SortfuncT,TAllocator>;
		using key_type=KeyT;
		using mapped_type=ValueT;
		using key_compare=SortfuncT;
		using value_compare=typename _Mybase::value_compare;
		using value_type=typename _Mybase::value_type;
		using allocator_type=typename _Mybase::allocator_type;
		using size_type=typename _Mybase::size_type;
		using difference_type=typename _Mybase::difference_type;
		using pointer=typename _Mybase::pointer;
		using const_pointer=typename _Mybase::const_pointer;
		using reference=value_type&;
		using const_reference=const value_type&;
		using iterator=typename _Mybase::iterator;
		using const_iterator=typename _Mybase::const_iterator;
		using reverse_iterator=typename _Mybase::reverse_iterator;
		using const_reverse_iterator=typename _Mybase::const_reverse_iterator;

		//using _Alnode=typename _Mybase::_Alnode;
		//using _Alnode_traits=typename _Mybase::_Alnode_traits;

		TMap() {}
		template<class TAllocator2>
		TMap(const std::map<KeyT,ValueT,SortfuncT,TAllocator2> & cpy)
			:std::map<KeyT,ValueT,SortfuncT,TAllocator>(cpy.begin(),cpy.end())
		{}
		template<class TAllocator2>
		operator std::map<KeyT,ValueT,SortfuncT,TAllocator2>()const
		{
			return std::map<KeyT,ValueT,SortfuncT,TAllocator2>(this->begin(),this->end());
		}
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
	template<typename KeyT,typename ValueT,class HashT=std::hash<KeyT>,
		class KeyEqualT=std::equal_to<KeyT>
		,class TAllocator=TDevilXAllocator<std::pair<const KeyT,ValueT> > >
	class TUnorderedMap
		:public std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator>
		,public TMemoryAllocatorObject<TUnorderedMap<KeyT,ValueT,HashT,KeyEqualT,TAllocator> >
	{
	public:
		using std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator>::unordered_map;
		using std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator>::operator[];
		using std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator>::operator=;

		using _Mybase=std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator>;
		using hasher=typename _Mybase::hasher;
		using key_type=typename _Mybase::key_type;
		using mapped_type=typename _Mybase::mapped_type;
		using key_equal=typename _Mybase::key_equal;
		using value_type=typename _Mybase::value_type;
		using allocator_type=typename _Mybase::allocator_type;
		//using size_type=typename _Mybase::size_type;
		//using difference_type=typename _Mybase::difference_type;
		using pointer=typename _Mybase::pointer;
		using const_pointer=typename _Mybase::const_pointer;
		using reference=value_type&;
		using const_reference=const value_type&;
		using iterator=typename _Mybase::iterator;
		using const_iterator=typename _Mybase::const_iterator;

		TUnorderedMap()
		{
		}
		template<class TAllocator2>
		TUnorderedMap(const std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator2> & cpy)
			:std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator>(cpy.begin(),cpy.end())
		{
		}
		template<class TAllocator2>
		operator std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator2>()const
		{
			return std::unordered_map<KeyT,ValueT,HashT,KeyEqualT,TAllocator2>(this->begin(),this->end());
		}
		Boolean has(KeyT const & key)const
		{
			return _Mybase::find(key)!=this->end();
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

	typedef std::basic_string<Char,std::char_traits<Char>,TDevilXAllocator<Char> > String;
	typedef std::basic_string<WChar,std::char_traits<WChar>,TDevilXAllocator<WChar> > WString;
	typedef std::basic_stringstream<Char,std::char_traits<Char>,TDevilXAllocator<Char> > StringStream;
	typedef std::basic_stringstream<WChar,std::char_traits<WChar>,TDevilXAllocator<WChar> > WStringStream;
#ifdef UNICODE
	typedef WString TString;
	typedef WStringStream TStringStream;
#else
	typedef String TString;
	typedef StringStream TStringStream;
#endif
}
