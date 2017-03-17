#pragma once
#include "CommonUTFChar.h"
namespace NSDevilX
{
	class CUTF8String
	{
	protected:
		TVector<CUTF8Char> mString;
	public:
		CUTF8String(const String & text);
		CUTF8String(const WString & text);
		operator WString()const;
	};
}