#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CUTF8Char::CUTF8Char(Int32 c)
{
	mCode=c;
	_encode();
#if DEVILX_DEBUG
	CUTF16Char utf16_ch(mCode);
	TUTFString<CUTF16Char> utf16_str;
	utf16_str+=utf16_ch;
	mDebug.resize(utf16_str.size());
	memcpy(&mDebug[0],&utf16_str[0],utf16_str.size()*2);
#endif
}

NSDevilX::CUTF8Char::CUTF8Char(ConstVoidPtr buffer)
{
	const auto byte_buffer=static_cast<ConstBytePtr>(buffer);
	auto c=byte_buffer[0];
	if(c&0x80)
	{
		UInt32 byte_count=0;
		for(int bit=0;bit<8;++bit)
		{
			if((c>>(8-bit-1))&0x1)
				++byte_count;
			else
				break;
		}
		assert(byte_count>=2);
		for(UInt32 byte_index=0;byte_index<byte_count;++byte_index)
			mBuffer.push_back(byte_buffer[byte_index]);
	}
	else
	{
		mBuffer.push_back(c);
	}
	_decode();
#if DEVILX_DEBUG
	CUTF16Char utf16_ch(mCode);
	TUTFString<CUTF16Char> utf16_str;
	utf16_str+=utf16_ch;
	mDebug.resize(utf16_str.size());
	memcpy(&mDebug[0],&utf16_str[0],utf16_str.size()*2);
#endif
}

Void NSDevilX::CUTF8Char::_decode()
{
	auto c=mBuffer[0];
	if(c&0x80)
	{
		UInt32 byte_count=0;
		for(int bit=0;bit<8;++bit)
		{
			if((c>>(8-bit-1))&0x1)
				++byte_count;
			else
				break;
		}
		assert(byte_count>=2);
		mCode=0;
		for(Int32 byte_index=byte_count-1;byte_index>=0;--byte_index)
		{
			Byte b=mBuffer[byte_index];
			if(byte_index==0)
			{
				mCode|=(b&0x1f)<<((byte_count-1)*6);
			}
			else
			{
				mCode|=(b&0x3f)<<((byte_count-byte_index-1)*6);
			}
		}
	}
	else
	{
		mCode=c;
	}
}

Void NSDevilX::CUTF8Char::_encode()
{
	const auto uint_code=*reinterpret_cast<UInt32*>(&mCode);
	//0xxxxxxx
	if(uint_code<128)
	{
		mBuffer.push_back(static_cast<Byte>(uint_code));
	}
	//110xxxxx 10xxxxxx
	else if(uint_code<2048)
	{
		Byte part=static_cast<Byte>(uint_code>>6);
		part|=0xc0;
		mBuffer.push_back(part);

		part=uint_code&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//1110xxxx 10xxxxxx 10xxxxxx
	else if(uint_code<65536)
	{
		Byte part=static_cast<Byte>(uint_code>>12);
		part|=0xe0;
		mBuffer.push_back(part);

		part=(uint_code>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=uint_code&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if(uint_code<2097152)
	{
		Byte part=static_cast<Byte>(uint_code>>18);
		part|=0xf0;
		mBuffer.push_back(part);

		part=(uint_code>>12)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=(uint_code>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=uint_code&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if(uint_code<67108864)
	{
		Byte part=static_cast<Byte>(uint_code>>24);
		part|=0xf8;
		mBuffer.push_back(part);

		part=(uint_code>>18)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=(uint_code>>12)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=(uint_code>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=uint_code&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if(uint_code<2147483648)
	{
		Byte part=static_cast<Byte>(uint_code>>30);
		part|=0xfc;
		mBuffer.push_back(part);

		part=(uint_code>>24)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=(uint_code>>18)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=(uint_code>>12)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=(uint_code>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=uint_code&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	else
	{
		assert(0);
	}
}

NSDevilX::CUTF16Char::CUTF16Char(Int32 c,Bool bigEndian)
	:mBigEndian(bigEndian)
{
	mCode=c;
	_encode();
#if DEVILX_DEBUG
	TUTFString<CUTF16Char> utf16_str;
	utf16_str+=*this;
	mDebug.resize(utf16_str.size());
	memcpy(&mDebug[0],&utf16_str[0],utf16_str.size()*2);
#endif
}

NSDevilX::CUTF16Char::CUTF16Char(ConstVoidPtr buffer,Bool bigEndian)
	:mBigEndian(bigEndian)
{
	const auto byte_buffer=static_cast<ConstBytePtr>(buffer);
	UInt16 first_uint16;
	if(isBigEndian())
		first_uint16=(byte_buffer[0]<<8)|byte_buffer[1];
	else
		first_uint16=(byte_buffer[1]<<8)|byte_buffer[0];
	if((first_uint16<0xd800)||(first_uint16>0xdfff))
	{
		mBuffer.push_back(byte_buffer[0]);
		mBuffer.push_back(byte_buffer[1]);
	}
	else
	{
		mBuffer.push_back(byte_buffer[0]);
		mBuffer.push_back(byte_buffer[1]);
		mBuffer.push_back(byte_buffer[2]);
		mBuffer.push_back(byte_buffer[3]);
	}
	_decode();
#if DEVILX_DEBUG
	TUTFString<CUTF16Char> utf16_str;
	utf16_str+=*this;
	mDebug.resize(utf16_str.size());
	memcpy(&mDebug[0],&utf16_str[0],utf16_str.size()*2);
#endif
}

Void NSDevilX::CUTF16Char::_decode()
{
	UInt16 first_uint16;
	if(isBigEndian())
		first_uint16=(mBuffer[0]<<8)|mBuffer[1];
	else
		first_uint16=(mBuffer[1]<<8)|mBuffer[0];
	if(mBuffer.size()==2)
	{
		assert((first_uint16<0xd800)||(first_uint16>0xdfff));
		mCode=first_uint16;
	}
	else
	{
		UInt16 second_uint16;
		if(isBigEndian())
			second_uint16=(mBuffer[2]<<8)|mBuffer[3];
		else
			second_uint16=(mBuffer[3]<<8)|mBuffer[2];
		assert(mBuffer.size()==4);
		assert((first_uint16>=0xd800)&&(first_uint16<=0xdbff));
		assert((second_uint16>=0xdc00)&&(second_uint16<=0xdfff));
		auto high_10=first_uint16-0xd800;
		high_10<<=10;
		auto low_10=second_uint16-0xdc00;
		mCode=(high_10|low_10)+0x10000;
	}
}

Void NSDevilX::CUTF16Char::_encode()
{
	auto uint_code=*reinterpret_cast<UInt32*>(&mCode);
	if(uint_code<=0xffff)
	{
		if(isBigEndian())
		{
			mBuffer.push_back(static_cast<UInt16>(uint_code)>>8);
			mBuffer.push_back(static_cast<UInt16>(uint_code)&0xff);
		}
		else
		{
			mBuffer.push_back(static_cast<UInt16>(uint_code)&0xff);
			mBuffer.push_back(static_cast<UInt16>(uint_code)>>8);
		}
	}
	else
	{
		assert(uint_code<=0x10ffff);
		uint_code-=0x10000;
		UInt16 high=static_cast<UInt16>((uint_code>>10)+0xd800);
		UInt16 low=static_cast<UInt16>((uint_code&0x3ff)+0xdc00);
		if(isBigEndian())
		{
			mBuffer.push_back(high>>8);
			mBuffer.push_back(high&0xff);
			mBuffer.push_back(low>>8);
			mBuffer.push_back(low&0xff);
		}
		else
		{
			mBuffer.push_back(high&0xff);
			mBuffer.push_back(high>>8);
			mBuffer.push_back(low&0xff);
			mBuffer.push_back(low>>8);
		}
	}
}
