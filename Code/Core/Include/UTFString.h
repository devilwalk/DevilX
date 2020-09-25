#pragma once

namespace NSDevilX
{
	namespace NSCore
	{
		class CUTF8String
			:public TUTFString<CUTF8Char,TDevilXAllocator<CUTF8Char> >
		{
		public:
			using TUTFString<CUTF8Char,TDevilXAllocator<CUTF8Char> >::TUTFString;
			template<class TAllocator>
			operator std::vector<CUTF16Char,TAllocator>()const
			{
				NSDevilX::TUTFString<CUTF16Char,TAllocator> ret;
				for(auto const & c:*this)
				{
					ret+=CUTF16Char(c);
				}
				return ret;
			}
		};
		class CUTF16String
			:public TUTFString<CUTF16Char,TDevilXAllocator<CUTF16Char> >
		{
		public:
			using TUTFString<CUTF16Char,TDevilXAllocator<CUTF16Char> >::TUTFString;
			CUTF16String(ConstVoidPtr utf16Buffer,SizeT sizeInBytes,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
			template<class TAllocator>
			CUTF16String(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & ansiiText,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN)
			{
				for(auto c:ansiiText)
					push_back(CUTF16Char(c,bigEndian));
			}
			template<class TAllocator>
			CUTF16String(const std::basic_string<WChar,std::char_traits<WChar>,TAllocator> & utf16Text,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN)
			{
				for(auto c:utf16Text)
					push_back(CUTF16Char(c,bigEndian));
			}
			template<class TAllocator>
			operator std::vector<CUTF8Char,TAllocator>()const
			{
				NSDevilX::TUTFString<CUTF8Char,TAllocator> ret;
				for(auto const & c:*this)
				{
					ret+=CUTF8Char(c);
				}
				return ret;
			}
		};
	}
}