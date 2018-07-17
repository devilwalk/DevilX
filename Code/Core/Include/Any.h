#pragma once
#include "Define.h"
#include "Type.h"
#include "MemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CAny
		:public TBaseObject<CAny>
	{
	public:
		struct SBaseHolder
		{
			virtual ~SBaseHolder(){}
			virtual Void setValue(ConstVoidPtr value)=0;
			virtual ConstVoidPtr getValue()const=0;
			virtual Boolean isEqual(ConstVoidPtr value)const=0;
			virtual SBaseHolder * clone()const=0;
		};
		template<typename T>
		struct THolder
			:public SBaseHolder
			,public TBaseObject<THolder<T> >
		{
			T mValue;
			THolder(const T & value)
				:mValue(value)
			{}
			virtual Void setValue(ConstVoidPtr value) override
			{
				mValue=*static_cast<const T*>(value);
			}
			virtual ConstVoidPtr getValue() const override
			{
				return &mValue;
			}
			virtual Boolean isEqual(ConstVoidPtr value) const override
			{
				return mValue==*static_cast<const T*>(value);
			}
			virtual SBaseHolder * clone() const override
			{
				return DEVILX_NEW THolder<T>(mValue);
			}
		};
	protected:
		SBaseHolder * mValue;
	public:
		CAny()
			:mValue(nullptr)
		{}
		template<typename T>
		CAny(T const & t)
			:mValue(nullptr)
		{
			*this=t;
		}
		CAny(const CAny & t)
			:mValue(nullptr)
		{
			*this=t;
		}
		~CAny()
		{
			delete(mValue);
		}
		const CAny & operator=(const CAny & t)
		{
			if(mValue)
				mValue->setValue(t.mValue->getValue());
			else if(t.mValue)
				mValue=t.mValue->clone();
			return *this;
		}
		template<typename T>
		const CAny & operator=(const T & t)
		{
			if(mValue)
				mValue->setValue(&t);
			else
				mValue=new THolder<T>(t);
			return *this;
		}
		Boolean operator==(const CAny & t)const
		{
			if(isValidate()&&t.isValidate())
				return mValue->isEqual(t.mValue->getValue());
			else
				return isValidate()==t.isValidate();
		}
		template<typename T>
		Boolean operator==(const T & t)const
		{
			if(isValidate()&&t.isValidate())
				return mValue->isEqual(&t);
			else
				return isValidate()==t.isValidate();

		}
		Boolean isValidate()const
		{
			return nullptr!=mValue;
		}
		template<typename T>
		const T & get()const
		{
			assert(mValue);
			return *reinterpret_cast<const T*>(mValue->getValue());
		}
	};
}
