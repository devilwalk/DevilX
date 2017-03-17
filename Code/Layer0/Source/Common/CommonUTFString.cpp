#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CUTF8String::CUTF8String(const String & text)
{
	for(auto c:text)
		mString.push_back(c);
}

NSDevilX::CUTF8String::CUTF8String(const WString & text)
{
	for(auto c:text)
		mString.push_back(c);
}

NSDevilX::CUTF8String::operator WString() const
{
	WString ret;
	for(auto const & c:mString)
		ret.push_back(static_cast<WChar>(c));
	return ret;
}
