#pragma once
#include "UtilitySTL.h"
namespace NSDevilX
{
	class CModule
		:public TBaseObject<CModule>
	{
	public:
		typedef Void(*ProAddress)();
	protected:
		VoidPtr mInternalResource;
	public:
		CModule(const String & fullName);
		~CModule();
		ProAddress getProcAddress(const String & name)const;
	};
}