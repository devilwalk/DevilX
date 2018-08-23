#pragma once
#include "UtilityReadWriteLocker.h"
namespace NSDevilX
{
	template<typename T>
	class TSharedReadDataBase
	{
	protected:
		T * mData;
		CReadWriteLocker mLocker;
	public:
		operator T()
		{
			T ret;
			read(ret);
			return ret;
		}
		T const & beginRead()
		{
			mLocker.lockRead();
			return _get();
		}
		T const & beginUniqueRead()
		{
			return beginWrite();
		}
		Void endRead()
		{
			mLocker.unLockRead();
		}
		T & beginWrite()
		{
			mLocker.lockWrite();
			return _get();
		}
		Void endWrite()
		{
			mLocker.unLockWrite();
		}
		Boolean tryBeginRead(T & t)
		{
			Boolean ret=mLocker.tryLockRead();
			if(ret)
				t=_get();
			return ret;
		}
		Boolean tryBeginWrite(T const & t)
		{
			Boolean ret=mLocker.tryLockWrite();
			if(ret)
				_get()=t;
			return ret;
		}
		Void read(T & t)
		{
			t=beginRead();
			endRead();
		}
		Void write(T const & t)
		{
			beginWrite()=t;
			endWrite();
		}
	protected:
		TSharedReadDataBase()
			:mData(0)
		{
		}
		~TSharedReadDataBase()
		{
		}
		virtual T & _get()=0;
	};
	template<typename T>
	class TSharedReadData
		:public TSharedReadDataBase<T>
	{
	public:
		TSharedReadData()
		{
		}
		explicit TSharedReadData(T const & t)
		{
			_get()=t;
		}
		~TSharedReadData()
		{
			if(this->mData)
			{
				DEVILX_FREE(this->mData);
			}
		}
		virtual T & _get() override
		{
			if(!this->mData)
			{
				this->mData=static_cast<decltype(this->mData)>(DEVILX_ALLOC(sizeof(T)));
			}
			return *this->mData;
		}
	};
	template<class T>
	class TSharedReadObject
		:public TSharedReadDataBase<T>
	{
	public:
		TSharedReadObject()
		{
		}
		explicit TSharedReadObject(T const & t)
		{
			this->mData=DEVILX_NEW T(t);
		}
		~TSharedReadObject()
		{
			DEVILX_DELETE(this->mData);
		}
		virtual T & _get() override
		{
			if(!this->mData)
			{
				this->mData=DEVILX_NEW T;
			}
			return *this->mData;
		}
	};
}
