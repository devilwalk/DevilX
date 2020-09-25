#pragma once
#include "CommonType.h"
#include "CommonDefine.h"
namespace NSDevilX
{
	class CReferenceObject
		:public TMemoryAllocatorObject<CReferenceObject>
	{
	protected:
		Int32 mRefCount;
	public:
		CReferenceObject()
			:mRefCount(1)
		{}
		virtual Void addRef()
		{
			++mRefCount;
		}
		virtual Void release()
		{
			--mRefCount;
			if(0>=mRefCount)
				delete(this);
		}
		virtual Int32 getRef()const
		{
			return mRefCount;
		}
	protected:
		virtual ~CReferenceObject()
		{
			assert(0==getRef());
		}
	};
	class CReferenceObjectMT
		:public TMemoryAllocatorObject<CReferenceObjectMT>
	{
	protected:
		std::atomic<Int32> mRefCount;
	public:
		CReferenceObjectMT():mRefCount(1){}
		virtual Void addRef()
		{
			++mRefCount;
		}
		virtual Void release(Boolean del=true)
		{
			--mRefCount;
			if(del)
			{
				if(0>=getRef())
				{
					delete(this);
				}
			}
			else
			{
				assert(getRef()>=0);
			}
		}
		virtual Int32 getRef()const
		{
			return mRefCount;
		}
	protected:
		virtual ~CReferenceObjectMT()
		{
			assert(0==getRef());
		}
	};
}