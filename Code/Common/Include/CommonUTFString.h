#pragma once
#include "CommonUTFChar.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	template<class TUTFChar,class TAllocator=std::allocator<TUTFChar> >
	class TUTFString
		:public TVector<TUTFChar,TAllocator>
	{
	public:
		using TVector<TUTFChar,TAllocator>::TVector;
		using TVector<TUTFChar,TAllocator>::operator[];
		using TVector<TUTFChar,TAllocator>::operator=;
		TUTFString()
		{
		}
		TUTFString(const std::vector<TUTFChar,TAllocator> & cpy)
			:TVector<TUTFChar,TAllocator>(cpy)
		{
		}
		TUTFString(ConstVoidPtr utfCharBuffer,SizeT sizeInBytes)
		{
			const auto src_addr=reinterpret_cast<SizeT>(utfCharBuffer);
			auto dst_addr=src_addr;
			while(sizeInBytes>dst_addr-src_addr)
			{
				TUTFChar ch(reinterpret_cast<ConstVoidPtr>(dst_addr));
				this->push_back(ch);
				dst_addr+=ch.getBuffer().size();
			}
			assert(sizeInBytes==dst_addr-src_addr);
		}
		template<class TUTFChar2,class TAllocator2>
		TUTFString(const std::vector<TUTFChar2,TAllocator2> & cpy)
		{
			for(auto const & ch:cpy)
				this->push_back(TUTFChar(ch));
		}
		TUTFString operator +(Int32 ch)const
		{
			auto ret=*this;
			ret.push_back(ch);
			return ret;
		}
		TUTFString operator +(ConstCharPtr text)const
		{
			std::string str_text=text;
			return (*this)+str_text;
		}
		TUTFString operator +(ConstWCharPtr text)const
		{
			std::wstring str_text=text;
			return (*this)+str_text;
		}
		template<typename TUTFChar2,class TAllocator2>
		TUTFString operator +(const std::vector<TUTFChar2,TAllocator2> & text)const
		{
			auto ret=*this;
			ret.insert(ret.end(),text.begin(),text.end());
			return ret;
		}
		template<class TAllocator2>
		TUTFString operator +(std::basic_string<Char,std::char_traits<Char>,TAllocator2> text)const
		{
			auto ret=*this;
			ret.insert(ret.end(),text.begin(),text.end());
			return ret;
		}
		template<class TAllocator2>
		TUTFString operator +(std::basic_string<WChar,std::char_traits<WChar>,TAllocator2> text)const
		{
			auto ret=*this;
			ret.insert(ret.end(),text.begin(),text.end());
			return ret;
		}
		TUTFString operator -(SizeT count)const
		{
			auto ret=*this;
			while(count--)
				ret.pop_back();
			return ret;
		}
		template<typename T>
		TUTFString & operator +=(const T & t)
		{
			*this=*this+t;
			return *this;
		}
		TUTFString & operator -=(SizeT count)
		{
			while(count--)
				this->pop_back();
			return *this;
		}
		template<class TAllocator2>
		operator std::basic_string<WChar,std::char_traits<WChar>,TAllocator2>()const
		{
			auto utf16_string=NSDevilX::TUTFString<CUTF16Char>(*this);
			std::basic_string<WChar,std::char_traits<WChar>,TAllocator2> ret;
			for(auto const & c:utf16_string)
			{
				auto p=reinterpret_cast<ConstWCharPtr>(&c.getBuffer()[0]);
				ret.push_back(*p);
				if(c.getBuffer().size()>2)
				{
					assert(c.getBuffer().size()==4);
					ret.push_back(*(p+1));
				}
			}
			return ret;
		}
		template<class TAllocator2=std::allocator<Byte> >
		std::vector<Byte,TAllocator2> toBytes()const
		{
			std::vector<Byte,TAllocator2> ret;
			for(auto const & ch:*this)
			{
				ret.insert(ret.end(),ch.getBuffer().begin(),ch.getBuffer().end());
			}
			return ret;
		}
		template<class TAllocator2=std::allocator<Char> >
		std::basic_string<Char,std::char_traits<Char>,TAllocator2> toString()const
		{
			std::basic_string<Char,std::char_traits<Char>,TAllocator2> ret;
			for(auto const & ch:*this)
			{
				ret.insert(ret.end(),ch.getBuffer().begin(),ch.getBuffer().end());
			}
			return ret;
		}
	};

	typedef TUTFString<CUTF8Char> CUTF8String;
	typedef TUTFString<CUTF16Char> CUTF16String;
}