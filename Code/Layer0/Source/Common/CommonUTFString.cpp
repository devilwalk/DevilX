#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CUTF8String::CUTF8String(const TUTFString<CUTF16Char> & src)
{
	for(const auto & c:src)
	{
		(*this)+=CUTF8Char(static_cast<Int32>(c));
	}
}

NSDevilX::CUTF8String::operator TUTFString<CUTF16Char>() const
{
	TUTFString<CUTF16Char> ret;
	for(auto const & c:*this)
	{
		ret+=CUTF16Char(c);
	}
	return ret;
}

NSDevilX::CUTF16String::CUTF16String(ConstVoidPtr utf16Buffer,SizeT sizeInBytes,Bool bigEndian)
{
	const auto src_addr=reinterpret_cast<SizeT>(utf16Buffer);
	auto dst_addr=src_addr;
	while(sizeInBytes>dst_addr-src_addr)
	{
		CUTF16Char ch(reinterpret_cast<ConstVoidPtr>(dst_addr),bigEndian);
		push_back(ch);
		dst_addr+=ch.getBuffer().size();
	}
	assert(sizeInBytes==dst_addr-src_addr);
}

NSDevilX::CUTF16String::CUTF16String(const String & ansiiText,Bool bigEndian)
{
	for(auto c:ansiiText)
		push_back(CUTF16Char(c,bigEndian));
}

NSDevilX::CUTF16String::CUTF16String(const WString & utf16Text,Bool bigEndian)
{
	for(auto c:utf16Text)
		push_back(CUTF16Char(c,bigEndian));
}

NSDevilX::CUTF16String::operator WString() const
{
	WString ret;
	for(auto const & c:*this)
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
