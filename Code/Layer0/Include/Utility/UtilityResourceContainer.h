#pragma once
#include "UtilitySTLMT.h"
namespace NSDevilX
{
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
	template<typename KeyT,class ValueT>
	class TResourcePtrMapMT
		:public TMapMT<KeyT,ValueT*>
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
	template<typename KeyT,class ValueT>
	class TRefResourcePtrMapMT
		:public TMapMT<KeyT,ValueT*>
	{
	public:
		virtual ~TRefResourcePtrMapMT()
		{
			destroyAllMT();
		}
		Void destroy(const KeyT & key)
		{
			auto iter=this->find(key);
			iter->second->release();
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
}
