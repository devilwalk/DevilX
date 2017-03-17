#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CUTF8Char::CUTF8Char(Int32 c)
{
	//0xxxxxxx
	if(c<128)
	{
		mBuffer.push_back(static_cast<Char>(c));
	}
	//110xxxxx 10xxxxxx
	else if(c<2048)
	{
		Char part=static_cast<Char>(c>>6);
		part|=0xc0;
		mBuffer.push_back(part);

		part=c&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//1110xxxx 10xxxxxx 10xxxxxx
	else if(c<65535)
	{
		Char part=static_cast<Char>(c>>12);
		part|=0xe0;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=c&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if(c<2097152)
	{
		Char part=static_cast<Char>(c>>18);
		part|=0xf0;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>12)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=c&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if(c<67108864)
	{
		Char part=static_cast<Char>(c>>24);
		part|=0xf8;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>18)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>12)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=c&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if(c<2147483648)
	{
		Char part=static_cast<Char>(c>>30);
		part|=0xfc;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>24)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>18)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>12)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=static_cast<Char>(c>>6)&0x3f;
		part|=0x80;
		mBuffer.push_back(part);

		part=c&0x3f;
		part|=0x80;
		mBuffer.push_back(part);
	}
	else
	{
		assert(0);
	}
}

NSDevilX::CUTF8Char::operator WChar() const
{
	auto ret=static_cast<Int32>(*this);
	assert((ret<37268)&&(ret>-37268));
	return static_cast<WChar>(ret);
}

NSDevilX::CUTF8Char::operator Int32() const
{
	Int32 ret=0xffffffff;
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
		ret=0;
		for(Int32 byte_index=byte_count-1;byte_index>=0;--byte_index)
		{
			Byte b=mBuffer[byte_index];
			if(byte_index==0)
			{
				ret|=(b&0x1f)<<((byte_count-1)*6);
			}
			else
			{
				ret|=(b&0x3f)<<((byte_count-byte_index-1)*6);
			}
		}
	}
	else
	{
		ret=c;
	}
	return ret;
}