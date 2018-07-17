#pragma once
#include "STL.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CUTFChar
		{
		protected:
			Int32 mCode;
			TVector<Byte> mBuffer;
#if DEVILX_DEBUG
			WString mDebug;
#endif
		public:
			explicit operator Char()const
			{
				Int32 ret=*this;
				assert((ret<128)&&(ret>=-128));
				return static_cast<Char>(ret);
			}
			explicit operator WChar()const
			{
				Int32 ret=*this;
				assert((ret<37268)&&(ret>=-37268));
				return static_cast<WChar>(ret);
			}
			operator Int32()const
			{
				return mCode;
			}
			const decltype(mBuffer) & getBuffer()const
			{
				return mBuffer;
			}
		};
		class CUTF8Char
			:public TBaseObject<CUTF8Char>
			,public CUTFChar
		{
		public:
			CUTF8Char(Int32 c);
			CUTF8Char(ConstVoidPtr buffer);
		protected:
			Void _decode();
			Void _encode();
		};
		class CUTF16Char
			:public TBaseObject<CUTF16Char>
			,public CUTFChar
		{
		protected:
			const Bool mBigEndian;
		public:
			CUTF16Char(Int32 c,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
			CUTF16Char(ConstVoidPtr buffer,Bool bigEndian=DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN);
			Bool isBigEndian()const
			{
				return mBigEndian;
			}
		protected:
			Void _decode();
			Void _encode();
		};
	}
}