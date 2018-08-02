#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CUTF16String::CUTF16String(ConstVoidPtr utf16Buffer,SizeT sizeInBytes,Bool bigEndian)
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