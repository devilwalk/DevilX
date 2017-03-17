#pragma once
#include "CommonSTL.h"
namespace NSDevilX
{
	class CUTF8Char
		:public TBaseObject<CUTF8Char>
	{
	protected:
		String mBuffer;
	public:
		CUTF8Char(Int32 c);
		explicit operator WChar()const;
		explicit operator Int32()const;
		const String & getBuffer()const
		{
			return mBuffer;
		}
	};
}