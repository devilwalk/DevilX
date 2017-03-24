#pragma once
#include "CommonAny.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	class CUserDataContainer
	{
	public:
		typedef TMap<const String,CAny> Anys;
		typedef TMap<ConstVoidPtr,CAny> Anys2;
		typedef TVector<VoidPtr> Pointers;
	protected:
		Anys * mAnys;
		Anys2 * mAnys2;
		Pointers * mPointers;
	public:
		CUserDataContainer():mAnys(nullptr),mAnys2(nullptr),mPointers(nullptr)
		{}
		virtual ~CUserDataContainer()
		{
			DEVILX_DELETE(mAnys);
			DEVILX_DELETE(mAnys2);
			DEVILX_DELETE(mPointers);
		}
		Void setUserData(const String & name,const CAny & userAny)
		{
			_createAny();
			(*mAnys)[name]=userAny;
		}
		Void setUserData(ConstVoidPtr key,const CAny & userAny)
		{
			_createAny2();
			(*mAnys2)[key]=userAny;
		}
		Void setUserPointer(Pointers::size_type index,VoidPtr pointer)
		{
			_createPointers();
			if(mPointers->size()<=index)
				mPointers->resize(index+1);
			(*mPointers)[index]=pointer;
		}
		const CAny & getUserData(const String & name)const
		{
			assert(mAnys);
			return mAnys->get(name);
		}
		const CAny & getUserData(ConstVoidPtr key)const
		{
			assert(mAnys2);
			return mAnys2->get(key);
		}
		template<typename T>
		T * getUserPointer(Pointers::size_type index)const
		{
			assert(mPointers);
			return static_cast<T*>((*mPointers)[index]);
		}
		Boolean hasUserData(const String & name)const
		{
			return mAnys&&mAnys->has(name);
		}
		Boolean hasUserData(ConstVoidPtr key)const
		{
			return mAnys2&&mAnys2->has(key);
		}
		Boolean hasUserPointer(Pointers::size_type index)const
		{
			return mPointers&&(mPointers->size()>index);
		}
		Void removeUserData(const String & name)
		{
			if(mAnys)
			{
				mAnys->erase(name);
			}
		}
		Void removeUserData(ConstVoidPtr key)
		{
			if(mAnys2)
			{
				mAnys2->erase(key);
			}
		}
	protected:
		Void _createAny()
		{
			if(!mAnys)
				mAnys=DEVILX_NEW Anys;
		}
		Void _createAny2()
		{
			if(!mAnys)
				mAnys2=DEVILX_NEW Anys2;
		}
		Void _createPointers()
		{
			if(!mPointers)
				mPointers=DEVILX_NEW Pointers;
		}
	};
}
