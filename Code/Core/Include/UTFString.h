#pragma once
#include "UTFChar.h"
namespace NSDevilX
{
	namespace NSCore
	{
		template<class TUTFChar>
		class TUTFString
			:public TVector<TUTFChar>
		{
		public:
			using TVector<TUTFChar>::TVector;
			using TVector<TUTFChar>::operator[];
			using TVector<TUTFChar>::operator=;
			TUTFString()
			{
			}
			TUTFString(const TVector<TUTFChar> & cpy)
				:TVector<TUTFChar>(cpy)
			{
			}
			TUTFString(ConstVoidPtr utfCharBuffer,SizeT sizeInBytes)
			{
				const auto src_addr=reinterpret_cast<SizeT>(utfCharBuffer);
				auto dst_addr=src_addr;
				while(sizeInBytes>dst_addr-src_addr)
				{
					TUTFChar ch(reinterpret_cast<ConstVoidPtr>(dst_addr));
					push_back(ch);
					dst_addr+=ch.getBuffer().size();
				}
				assert(sizeInBytes==dst_addr-src_addr);
			}
			TUTFString(const String & ansiiText)
			{
				for(auto c:ansiiText)
					push_back(c);
			}
			TUTFString operator +(const TUTFChar & ch)const
			{
				auto ret=*this;
				push_back(ch);
				return ret;
			}
			TUTFString operator +(const TUTFString & text)const
			{
				auto ret=*this;
				insert(ret.mString.end(),text.mString.begin(),text.mString.end());
				return ret;
			}
			TUTFString operator -(SizeT count)const
			{
				auto ret=*this;
				while(count--)
					pop_back();
				return ret;
			}
			TUTFString & operator +=(const TUTFChar & ch)
			{
				push_back(ch);
				return *this;
			}
			TUTFString & operator +=(const TUTFString & text)
			{
				insert(end(),text.begin(),text.end());
				return *this;
			}
			TUTFString & operator -=(SizeT count)const
			{
				while(count--)
					pop_back();
				return *this;
			}
			TVector<Byte> toBytes()const
			{
				TVector<Byte> ret;
				for(auto const & ch:*this)
				{
					ret.insert(ret.end(),ch.getBuffer().begin(),ch.getBuffer().end());
				}
				return ret;
			}
			String toString()const
			{
				String ret;
				for(auto const & ch:*this)
				{
					ret.insert(ret.end(),ch.getBuffer().begin(),ch.getBuffer().end());
				}
				return ret;
			}
		};
		class CUTF8String
			:public TUTFString<CUTF8Char>
		{
		public:
			CUTF8String()
			{
			};
			CUTF8String(const TUTFString<CUTF8Char> & src)
				:TUTFString<CUTF8Char>(src)
			{
			}
			CUTF8String(ConstVoidPtr utfCharBuffer,SizeT sizeInBytes)
				:TUTFString<CUTF8Char>(utfCharBuffer,sizeInBytes)
			{
			}
			CUTF8String(const String & ansiiText)
				:TUTFString<CUTF8Char>(ansiiText)
			{
			}
			CUTF8String(const TVector<CUTF16Char> & src);
			operator TVector<CUTF16Char>()const;
			operator WString()const;
		};
		class CUTF16String
			:public TUTFString<CUTF16Char>
		{
		public:
			CUTF16String()
			{
			}
			CUTF16String(const TVector<CUTF16Char> & src)
				:TUTFString<CUTF16Char>(src)
			{
			}
			CUTF16String(const TVector<CUTF8Char> & src);
			CUTF16String(ConstVoidPtr utf16Buffer,SizeT sizeInBytes,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
			CUTF16String(const String & ansiiText,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
			CUTF16String(const WString & utf16Text,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
			operator WString()const;
			operator TVector<CUTF8Char>()const;
		};
	}
}