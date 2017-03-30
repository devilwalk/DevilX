#pragma once
#include "CommonUTFChar.h"
namespace NSDevilX
{
	template<class TUTFChar>
	class TUTFString
	{
	protected:
		TVector<TUTFChar> mString;
	public:
		TUTFString(){}
		TUTFString(const TUTFString & src)
			:mString(src.mString)
		{}
		TUTFString(ConstVoidPtr utfCharBuffer,SizeT sizeInBytes)
		{
			const auto src_addr=reinterpret_cast<SizeT>(utfCharBuffer);
			auto dst_addr=src_addr;
			while(sizeInBytes>dst_addr-src_addr)
			{
				TUTFChar ch(reinterpret_cast<ConstVoidPtr>(dst_addr));
				mString.push_back(ch);
				dst_addr+=ch.getBuffer().size();
			}
			assert(sizeInBytes==dst_addr-src_addr);
		}
		TUTFString(const String & ansiiText)
		{
			for(auto c:ansiiText)
				mString.push_back(c);
		}
		Boolean operator==(const TUTFString & test)const
		{
			return mString==test.mString;
		}
		Boolean operator!=(const TUTFString & test)const
		{
			return mString!=test.mString;
		}
		const TUTFChar & operator[](SizeT index)const
		{
			return mString[index];
		}
		TUTFChar & operator[](SizeT index)
		{
			return mString[index];
		}
		TUTFString operator +(const TUTFChar & ch)const
		{
			auto ret=*this;
			ret.mString.push_back(ch);
			return ret;
		}
		TUTFString operator +(const TUTFString & text)const
		{
			auto ret=*this;
			ret.mString.insert(ret.mString.end(),text.mString.begin(),text.mString.end());
			return ret;
		}
		TUTFString & operator +=(const TUTFChar & ch)
		{
			mString.push_back(ch);
			return *this;
		}
		TUTFString & operator +=(const TUTFString & text)
		{
			mString.insert(mString.end(),text.mString.begin(),text.mString.end());
			return *this;
		}
		typename TVector<TUTFChar>::iterator begin()
		{
			return mString.begin();
		}
		typename TVector<TUTFChar>::iterator end()
		{
			return mString.end();
		}
		typename TVector<TUTFChar>::const_iterator cbegin()const
		{
			return mString.cbegin();
		}
		typename TVector<TUTFChar>::const_iterator cend()const
		{
			return mString.cend();
		}
		SizeT length()const
		{
			return mString.size();
		}
	};
	class CUTF16String;
	class CUTF8String
		:public TBaseObject<CUTF8String>
		,public TUTFString<CUTF8Char>
	{
	public:
		CUTF8String(){};
		CUTF8String(const TUTFString<CUTF8Char> & src)
			:TUTFString<CUTF8Char>(src)
		{}
		CUTF8String(ConstVoidPtr utfCharBuffer,SizeT sizeInBytes)
			:TUTFString<CUTF8Char>(utfCharBuffer,sizeInBytes)
		{}
		CUTF8String(const String & ansiiText)
			:TUTFString<CUTF8Char>(ansiiText)
		{}
		operator CUTF16String()const;
	};
	class CUTF16String
		:public TBaseObject<CUTF16String>
		,public TUTFString<CUTF16Char>
	{
	public:
		CUTF16String(){}
		CUTF16String(const TUTFString<CUTF16Char> & src)
			:TUTFString<CUTF16Char>(src)
		{}
		CUTF16String(ConstVoidPtr utf16Buffer,SizeT sizeInBytes,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
		CUTF16String(const String & ansiiText,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
		CUTF16String(const WString & utf16Text,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
		operator WString()const;
	};
}