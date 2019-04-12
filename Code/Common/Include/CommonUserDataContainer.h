#pragma once
#include "CommonAny.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	template<class TStringAllocator=std::allocator<Char>,class TAllocator1=std::allocator<std::pair<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,CAny> >,class TAllocator2=std::allocator<std::pair<ConstVoidPtr,CAny> >,class TAllocator3=std::allocator<VoidPtr> >
	class TUserDataContainer
	{
	public:
		typedef TUnorderedMap<const std::basic_string<Char,std::char_traits<Char>,TStringAllocator>,CAny,std::hash<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,std::equal_to<std::basic_string<Char,std::char_traits<Char>,TStringAllocator> >,TAllocator1> Anys;
		typedef TUnorderedMap<ConstVoidPtr,CAny,std::hash<ConstVoidPtr>,std::equal_to<ConstVoidPtr>,TAllocator2> Anys2;
		typedef TVector<VoidPtr,TAllocator3> Pointers;
	protected:
		Anys * mAnys;
		Anys2 * mAnys2;
		Pointers * mPointers;
	public:
		TUserDataContainer():mAnys(nullptr),mAnys2(nullptr),mPointers(nullptr)
		{}
		virtual ~TUserDataContainer()
		{
			delete(mAnys);
			delete(mAnys2);
			delete(mPointers);
		}
		Void setUserData(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name,const CAny & userAny)
		{
			_createAny();
			(*mAnys)[name]=userAny;
		}
		Void setUserData(ConstVoidPtr key,const CAny & userAny)
		{
			_createAny2();
			(*mAnys2)[key]=userAny;
		}
		Void setUserPointer(typename Pointers::size_type index,VoidPtr pointer)
		{
			_createPointers();
			if(mPointers->size()<=index)
				mPointers->resize(index+1);
			(*mPointers)[index]=pointer;
		}
		const CAny & getUserData(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)const
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
		T * getUserPointer(typename Pointers::size_type index)const
		{
			assert(mPointers);
			return static_cast<T*>((*mPointers)[index]);
		}
		Boolean hasUserData(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)const
		{
			return mAnys&&mAnys->has(name);
		}
		Boolean hasUserData(ConstVoidPtr key)const
		{
			return mAnys2&&mAnys2->has(key);
		}
		Boolean hasUserPointer(typename Pointers::size_type index)const
		{
			return mPointers&&(mPointers->size()>index);
		}
		Void removeUserData(const std::basic_string<Char,std::char_traits<Char>,TStringAllocator> & name)
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
				mAnys=new Anys;
		}
		Void _createAny2()
		{
			if(!mAnys)
				mAnys2=new Anys2;
		}
		Void _createPointers()
		{
			if(!mPointers)
				mPointers=new Pointers;
		}
	};
	typedef TUserDataContainer<> CUserDataContainer;
}
