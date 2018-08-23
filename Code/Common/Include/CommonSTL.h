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
