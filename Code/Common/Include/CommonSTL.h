#pragma once
namespace NSDevilX
{
	template<typename T,class TAllocator=std::allocator<T> >
	class TVector
		:public std::vector<T,TAllocator>
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
	};
	template<typename T,class TAllocator=std::allocator<T> >
	class TList
		:public std::list<T,TAllocator>
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
	template<typename T,class SortfuncT=std::less<T>,class TAllocator=std::allocator<T> >
	class TSet
		:public std::set<T,SortfuncT,TAllocator>
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
	template<typename KeyT,typename ValueT,class SortfuncT=std::less<KeyT>,class TAllocator=std::allocator<std::pair<KeyT,ValueT> > >
	class TMap
		:public std::map<KeyT,ValueT,SortfuncT,TAllocator>
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

		using _Alnode=typename _Mybase::_Alnode;
		using _Alnode_traits=typename _Mybase::_Alnode_traits;
		using _Pairib=typename _Mybase::_Pairib;

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
}
